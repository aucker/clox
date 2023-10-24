//
// Created by Aucker An on 2023/10/14.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

#ifdef DEBUG_PRINT_CODE
#include "debug.h"
#endif

typedef struct {
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT,  // =
    PREC_OR,          // or
    PREC_AND,         // and
    PREC_EQUALITY,    // == !=
    PREC_COMPARISON,  // < > <= >=
    PREC_TERM,        // + -
    PREC_FACTOR,      // * /
    PREC_UNARY,       // ! -
    PREC_CALL,        // . ()
    PREC_PRIMARY
} Precedence;

/*
 * C's syntax for function pointer types is so bad that I always hide it behind a typedef.
 *
 * ParseFn type is a simple typedef for a function type that takes no arguments and returns nothing.
 */
//typedef void (*ParseFn)();
typedef void (*ParseFn)(bool canAssign);

typedef struct {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
} ParseRule;

typedef struct {
    Token name;
    int depth;
} Local;

/*
 * This lets the compiler tell when it's compiling top-level code
 * versus the body of a function. Most of the compiler doesn't care
 * about this - that's why it's a useful abstraction - but in one or
 * two places the distinction is meaningful.
 */
typedef enum {
    TYPE_FUNCTION,
    TYPE_SCRIPT,
} FunctionType;

typedef struct Compiler {
    struct Compiler* enclosing;
    ObjFunction* function;
    FunctionType type;

    Local locals[UINT8_COUNT];
    int localCount;
    int scopeDepth;
} Compiler;

Parser parser;
Compiler* current = NULL;
//Chunk* compilingChunk;
//
//static Chunk* currentChunk() {
//    return compilingChunk;
//}

static Chunk* currentChunk() {
    return &current->function->chunk;
}

static void errorAt(Token* token, const char* message) {
    if (parser.panicMode) return;
    parser.panicMode = true;
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // Nothing
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

static void error(const char* message) {
    errorAt(&parser.previous, message);
}

// Handling syntax errors
static void errorAtCurrent(const char* message) {
    errorAt(&parser.current, message);
}

static void advance() {
    parser.previous = parser.current;

    for (;;) {
        parser.current = scanToken();
        if (parser.current.type != TOKEN_ERROR) break;

        errorAtCurrent(parser.current.start);
    }
}

static void consume(TokenType type, const char* message) {
    // if can parse, we use advance to parse
    if (parser.current.type == type) {
        advance();
        return;
    }

    // if not, we return an error message
    errorAtCurrent(message);
}

static bool check(TokenType type) {
    return parser.current.type == type;
}

static bool match(TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
}

static void emitByte(uint8_t byte) {
    writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
    emitByte(byte1);
    emitByte(byte2);
}

static void emitLoop(int loopStart) {
    emitByte(OP_LOOP);

    int offset = currentChunk()->count - loopStart + 2;
    if (offset > UINT16_MAX) error("Loop body too large.");

    emitByte((offset >> 8) & 0xff);
    emitByte(offset & 0xff);
}

static int emitJump(uint8_t instruction) {
    emitByte(instruction);
    emitByte(0xff);
    emitByte(0xff);
    return currentChunk()->count - 2;
}

static void emitReturn() {
    emitByte(OP_RETURN);
}

static uint8_t makeConstant(Value value) {
    int constant = addConstant(currentChunk(), value);
    if (constant > UINT8_MAX) {
        error("Too many constants in one chunk.");
        return 0;
    }

    return (uint8_t)constant;
}

static void emitConstant(Value value) {
    emitBytes(OP_CONSTANT, makeConstant(value));
}

static void patchJump(int offset) {
    // -2 to adjust for the bytecode for the jump offset itself
    int jump = currentChunk()->count - offset - 2;

    if (jump > UINT16_MAX) {
        error("Too much code to jump over.");
    }

    currentChunk()->code[offset] = (jump >> 8) & 0xff;
    currentChunk()->code[offset + 1] = jump & 0xff;
}

//static void initCompiler(Compiler* compiler) {
static void initCompiler(Compiler* compiler, FunctionType type) {
    compiler->enclosing = current;
    compiler->function = NULL;
    compiler->type = type;
    compiler->localCount = 0;
    compiler->scopeDepth = 0;
    compiler->function = newFunction();
    current = compiler;
    if (type != TYPE_SCRIPT) {
        current->function->name = copyString(parser.previous.start,
                                             parser.previous.length);
    }

    Local* local = &current->locals[current->localCount++];
    local->depth = 0;
    local->name.start = "";
    local->name.length = 0;
}

//static void endCompiler() {
static ObjFunction* endCompiler() {
    emitReturn();
    ObjFunction* function = current->function;

#ifdef DEBUG_PRINT_CODE
    if (!parser.hadError) {
//        disassembleChunk(currentChunk(), "code");
        disassembleChunk(currentChunk(), function->name != NULL
                         ? function->name->chars : "<script>");
    }
#endif

    current = current->enclosing;  // when a compiler finishes, it pops itself off the
                                // stack by restoring the previous compiler to be the new current one.
    return function;
}

static void beginScope() {
    current->scopeDepth++;
}

static void endScope() {
    current->scopeDepth--;

    /*
     * they linger on beyond the scope where they are declared.
     * When a block ends, we need to put them to rest.
     */
    while (current->localCount > 0 &&
           current->locals[current->localCount - 1].depth >
                current->scopeDepth) {
        emitByte(OP_POP);
        current->localCount--;
    }
}

static void expression();
static void statement();
static void declaration();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);

static uint8_t identifierConstant(Token* name) {
    return makeConstant(OBJ_VAL(copyString(name->start,
                                           name->length)));
}

static bool identifierEqual(Token* a, Token* b) {
    if (a->length != b->length) return false;
    return memcmp(a->start, b->start, a->length) == 0;
}

// This is the heart, how we resolve a local variable
/*
 * we walk the list of locals that are currently in scope. If one has the same
 * name as the identifier token, the identifier must refer to that variable. We've
 * just found it! We walk the array backward so that we find the *last* declared
 * variable with the identifier. That ensures that inner local variables correctly
 * shadow locals with the same name in surrounding scopes.
 */
static int resolveLocal(Compiler* compiler, Token* name) {
    for (int i = compiler->localCount - 1; i >= 0; i--) {
        Local* local = &compiler->locals[i];
        if (identifierEqual(name, &local->name)) {
            if (local->depth == -1) {
                error("Can't read local variable in its own initializer.");
            }
            return i;
        }
    }

    return -1;
}

static void addLocal(Token name) {
    if (current->localCount == UINT8_COUNT) {
        error("Too many local variables in function.");
        return;
    }

    Local* local = &current->locals[current->localCount++];
    local->name = name;
//    local->depth = current->scopeDepth;
    local->depth = -1;
}

static void declareVariable() {
    if (current->scopeDepth == 0) return;

    Token* name = &parser.previous;
    for (int i = current->localCount - 1; i >= 0; i--) {
        Local* local = &current->locals[i];
        if (local->depth != -1 && local->depth < current->scopeDepth) {
            break;
        }

        if (identifierEqual(name, &local->name)) {
            error("Already a variable with this name in this scope.");
        }
    }


    addLocal(*name);
}

static uint8_t parseVariable(const char* errorMessage) {
    consume(TOKEN_IDENTIFIER, errorMessage);

    declareVariable();
    if (current->scopeDepth > 0) return 0;

    return identifierConstant(&parser.previous);
}

static void markInitialized() {
    if (current->scopeDepth == 0) return;  // we check the scope first
    current->locals[current->localCount - 1].depth =
        current->scopeDepth;
}

static void defineVariable(uint8_t global) {
    if (current->scopeDepth > 0) {
        markInitialized();
        return;
    }

    emitBytes(OP_DEFINE_GLOBAL, global);
}

// a helper function argumentList() for call() helper func
static uint8_t argumentList() {
    uint8_t argCount = 0;
    if (!check(TOKEN_RIGHT_PAREN)) {
        do {
            expression();
            if (argCount == 255) {
                error("Can't have more than 255 arguments.");
            }
            argCount++;
        } while (match(TOKEN_COMMA));
    }
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after arguments.");
    return argCount;
}

static void and_(bool canAssign) {
    int endJump = emitJump(OP_JUMP_IF_FALSE);

    emitByte(OP_POP);
    parsePrecedence(PREC_AND);

    patchJump(endJump);
}

//static void binary() {
static void binary(bool canAssign) {
    TokenType operatorType = parser.previous.type;
    ParseRule* rule = getRule(operatorType);
    parsePrecedence((Precedence)(rule->precedence + 1));

    switch (operatorType) {
        case TOKEN_BANG_EQUAL:    emitBytes(OP_EQUAL, OP_NOT); break;
        case TOKEN_EQUAL_EQUAL:   emitByte(OP_EQUAL); break;
        case TOKEN_GREATER:       emitByte(OP_GREATER); break;
        case TOKEN_GREATER_EQUAL: emitBytes(OP_LESS, OP_NOT); break;
        case TOKEN_LESS:          emitByte(OP_LESS); break;
        case TOKEN_LESS_EQUAL:    emitBytes(OP_GREATER, OP_NOT); break;
        case TOKEN_PLUS:          emitByte(OP_ADD); break;
        case TOKEN_MINUS:         emitByte(OP_SUBTRACT); break;
        case TOKEN_STAR:          emitByte(OP_MULTIPLY); break;
        case TOKEN_SLASH:         emitByte(OP_DIVIDE); break;
        default: return;  // unreachable;
    }
}

// we need a helper function call()
static void call(bool canAssign) {
    uint8_t argCount = argumentList();
    emitBytes(OP_CALL, argCount);
}

//static void literal() {
static void literal(bool canAssign) {
    switch (parser.previous.type) {
        case TOKEN_FALSE: emitByte(OP_FALSE); break;
        case TOKEN_NIL: emitByte(OP_NIL); break;
        case TOKEN_TRUE: emitByte(OP_TRUE); break;
    }
}

//static void grouping() {
static void grouping(bool canAssign) {
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

static void expression() {
    // ?
    /*
     * We aren't ready to implement every kind of expression in Lox yet. we don't even have Booleans
     * number literals: 123
     * parentheses for grouping: (123)
     * Unary negation: -123
     * The Four Horsemen of the Arithmetic: + - * /
     */

    parsePrecedence(PREC_ASSIGNMENT);
}

static void block() {
    while (!check(TOKEN_RIGHT_BRACE) && !check(TOKEN_EOF)) {
        declaration();
    }

    consume(TOKEN_RIGHT_BRACE, "Expect '}' after block.");
}

static void function(FunctionType type) {
    Compiler compiler;
    initCompiler(&compiler, type);
    beginScope();

    consume(TOKEN_LEFT_PAREN, "Expect '(' after function name.");
    if (!check(TOKEN_RIGHT_PAREN)) {
        do {
            current->function->arity++;
            if (current->function->arity > 255) {
                errorAtCurrent("Can't have more than 255 parameters.");
            }
            uint8_t constant = parseVariable("Expect parameter namp.");
            defineVariable(constant);
        } while (match(TOKEN_COMMA));
    }
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after parameters.");
    consume(TOKEN_LEFT_BRACE, "Expect '{' before function body.");
    block();

    ObjFunction* function = endCompiler();
    emitBytes(OP_CONSTANT, makeConstant(OBJ_VAL(function)));
}

static void funDeclaration() {
    uint8_t global = parseVariable("Except function name.");
    markInitialized();
    function(TYPE_FUNCTION);
    defineVariable(global);
}

static void varDeclaration() {
    uint8_t global = parseVariable("Expect variable name.");

    if (match(TOKEN_EQUAL)) {
        expression();
    } else {
        emitByte(OP_NIL);
    }
    consume(TOKEN_SEMICOLON,
            "Expect ';' after variable declaration.");

    defineVariable(global);
}

static void expressionStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after expression.");
    emitByte(OP_POP);
}

static void forStatement() {
    beginScope();
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
    consume(TOKEN_SEMICOLON, "Expect ';'.");
    if (match(TOKEN_SEMICOLON)) {
        // No initializer.
    } else if (match(TOKEN_VAR)) {
        varDeclaration();
    } else {
        expressionStatement();
    }

    int loopStart = currentChunk()->count;
//    consume(TOKEN_SEMICOLON, "Expect ';'");
    int exitJump = -1;
    /*
     * Since the clause is optional, we need to see if it's actually present.
     * If the clause is omitted, the next token must be a semicolon, so we
     * look for that to tell. If there isn't a semicolon, there must be a
     * condition expression.
     *
     * In that case, we compile it. Then, just like with while, we emit a conditional
     * jump that exits the loop if the condition is falsey. Since the jump leaves
     * the value on the stack, we pop it before executing the body. That ensures
     * we discard the value when the condition is true.
     */
    if (!match(TOKEN_SEMICOLON)) {
        expression();
        consume(TOKEN_SEMICOLON, "Expect ';' after loop condition.");

        // Jump out of the loop if the condition is false.
        exitJump = emitJump(OP_JUMP_IF_FALSE);
        emitByte(OP_POP); // Condition
    }
//    consume(TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

    /*
     * It's optional. Since this is the last clause, when omitted, the next token will be
     * the closing parenthesis. When an increment is present, we need to compile it now,
     * but it shouldn't execute yet.
     */
    if (!match(TOKEN_RIGHT_PAREN)) {
        int bodyJump = emitJump(OP_JUMP);
        int incrementStart = currentChunk()->count;
        expression();
        emitByte(OP_POP);
        consume(TOKEN_RIGHT_PAREN, "Expect ')' after for clause.");

        emitLoop(loopStart);
        loopStart = incrementStart;
        patchJump(bodyJump);
    }

    statement();
    emitLoop(loopStart);

    if (exitJump != -1) {
        patchJump(exitJump);
        emitByte(OP_POP);  // Condition.
    }
    endScope();
}

static void ifStatement() {
    consume(TOKEN_LEFT_PAREN, "Except '(' after 'if'.");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Except ')' after condition.");

    int thenJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP);
    statement();

    int elseJump = emitJump(OP_JUMP);

    patchJump(thenJump);
    emitByte(OP_POP);

    if (match(TOKEN_ELSE)) statement();
    patchJump(elseJump);
}

static void printStatement() {
    expression();
    consume(TOKEN_SEMICOLON, "Expect ';' after value.");
    emitByte(OP_PRINT);
}

static void whileStatement() {
    int loopStart = currentChunk()->count;
    consume(TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
    expression();
    consume(TOKEN_RIGHT_PAREN, "Expect ')' after condition.");

    int exitJump = emitJump(OP_JUMP_IF_FALSE);
    emitByte(OP_POP);
    statement();
    emitLoop(loopStart);

    patchJump(exitJump);
    emitByte(OP_POP);
}

static void synchronize() {
    parser.panicMode = false;

    while (parser.current.type != TOKEN_EOF) {
        if (parser.previous.type == TOKEN_SEMICOLON) return;
        switch (parser.current.type) {
            case TOKEN_CLASS:
            case TOKEN_FUN:
            case TOKEN_VAR:
            case TOKEN_FOR:
            case TOKEN_IF:
            case TOKEN_WHILE:
            case TOKEN_PRINT:
            case TOKEN_RETURN:
                return;

            default:
                ;  // Do nothing
        }

        advance();
    }
}

static void declaration() {
//    statement();
    if (match(TOKEN_FUN)) {
        funDeclaration();
    } else if (match(TOKEN_VAR)) {
        varDeclaration();
    } else {
        statement();
    }

    if (parser.panicMode) synchronize();
}

static void statement() {
    if (match(TOKEN_PRINT)) {
        printStatement();
    } else if (match(TOKEN_FOR)) {
        forStatement();
    } else if (match(TOKEN_IF)) {
        ifStatement();
    } else if (match(TOKEN_WHILE)) {
        whileStatement();
    } else if (match(TOKEN_LEFT_BRACE)) {
        beginScope();
        block();
        endScope();
    } else {
        expressionStatement();
    }
}

//static void number() {
static void number(bool canAssign) {
    double value = strtod(parser.previous.start, NULL);
//    emitConstant(value);
    emitConstant(NUMBER_VAL(value));
}

static void or_(bool canAssign) {
    int elseJump = emitJump(OP_JUMP_IF_FALSE);
    int endJump = emitJump(OP_JUMP);

    patchJump(elseJump);
    emitByte(OP_POP);

    parsePrecedence(PREC_OR);
    patchJump(endJump);
}

//static void string() {
static void string(bool canAssign) {
    emitConstant(OBJ_VAL(copyString(parser.previous.start + 1,
                                    parser.previous.length - 2)));
}

//static void namedVariable(Token name) {
static void namedVariable(Token name, bool canAssign) {
//    uint8_t arg = identifierConstant(&name);
//    emitBytes(OP_GET_GLOBAL, arg);

//    if (match(TOKEN_EQUAL)) {
    uint8_t getOp, setOp;
    int arg = resolveLocal(current, &name);
    if (arg != -1) {
        getOp = OP_GET_LOCAL;
        setOp = OP_SET_LOCAL;
    } else {
        arg = identifierConstant(&name);
        getOp = OP_GET_GLOBAL;
        setOp = OP_SET_GLOBAL;
    }

    if (canAssign && match(TOKEN_EQUAL)) {
        expression();
//        emitBytes(OP_SET_GLOBAL, arg);
        emitBytes(setOp, (uint8_t)arg);
    } else {
//        emitBytes(OP_GET_GLOBAL, arg);
        emitBytes(getOp, (uint8_t)arg);
    }
}

//static void variable() {
//    namedVariable(parser.previous);
//}
static void variable(bool canAssign) {
    namedVariable(parser.previous, canAssign);
}

//static void unary() {
static void unary(bool canAssign) {
    TokenType operatorType = parser.previous.type;

    // Compile the operand
//    expression();
    parsePrecedence(PREC_UNARY);

    // Emit the operator instruction
    switch (operatorType) {
        case TOKEN_BANG: emitByte(OP_NOT); break;
        case TOKEN_MINUS: emitByte(OP_NEGATE); break;
        default: return;  // unreachable
    }
}

ParseRule rules[] = {
//        [TOKEN_LEFT_PAREN]      = {grouping, NULL,   PREC_NONE},
        [TOKEN_LEFT_PAREN]      = {grouping, call,   PREC_CALL},
        [TOKEN_RIGHT_PAREN]     = {NULL,     NULL,   PREC_NONE},
        [TOKEN_LEFT_BRACE]      = {NULL,     NULL,   PREC_NONE},
        [TOKEN_RIGHT_BRACE]     = {NULL,     NULL,   PREC_NONE},
        [TOKEN_COMMA]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_DOT]             = {NULL,     NULL,   PREC_NONE},
        [TOKEN_MINUS]           = {unary,    binary, PREC_TERM},
        [TOKEN_PLUS]            = {NULL,     binary, PREC_TERM},
        [TOKEN_SEMICOLON]       = {NULL,     NULL,   PREC_NONE},
        [TOKEN_SLASH]           = {NULL,     binary, PREC_FACTOR},
        [TOKEN_STAR]            = {NULL,     binary, PREC_FACTOR},
//        [TOKEN_BANG]            = {NULL,     NULL,   PREC_NONE},
        [TOKEN_BANG]            = {unary,    NULL,   PREC_NONE},
//        [TOKEN_BANG_EQUAL]      = {NULL,     NULL,   PREC_NONE},
        [TOKEN_BANG_EQUAL]      = {NULL,     binary, PREC_EQUALITY},
        [TOKEN_EQUAL]           = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_EQUAL_EQUAL]     = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_GREATER]         = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_GREATER_EQUAL]   = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_LESS]            = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_LESS_EQUAL]      = {NULL,     NULL,   PREC_NONE},
        [TOKEN_EQUAL_EQUAL]     = {NULL,     binary, PREC_EQUALITY},
        [TOKEN_GREATER]         = {NULL,     binary, PREC_COMPARISON},
        [TOKEN_GREATER_EQUAL]   = {NULL,     binary, PREC_COMPARISON},
        [TOKEN_LESS]            = {NULL,     binary, PREC_COMPARISON},
        [TOKEN_LESS_EQUAL]      = {NULL,     binary, PREC_COMPARISON},
//        [TOKEN_IDENTIFIER]      = {NULL,     NULL,   PREC_NONE},
        [TOKEN_IDENTIFIER]      = {variable, NULL,   PREC_NONE},
//        [TOKEN_STRING]          = {NULL,     NULL,   PREC_NONE},
        [TOKEN_STRING]          = {string,   NULL,   PREC_NONE},
        [TOKEN_NUMBER]          = {number,   NULL,   PREC_NONE},
//        [TOKEN_AND]             = {NULL,     NULL,   PREC_NONE},
        [TOKEN_AND]             = {NULL,     and_,   PREC_AND},
        [TOKEN_CLASS]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_ELSE]            = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_FALSE]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_FALSE]           = {literal,  NULL,   PREC_NONE},
        [TOKEN_FOR]             = {NULL,     NULL,   PREC_NONE},
        [TOKEN_FUN]             = {NULL,     NULL,   PREC_NONE},
        [TOKEN_IF]              = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_NIL]             = {NULL,     NULL,   PREC_NONE},
        [TOKEN_NIL]             = {literal,  NULL,   PREC_NONE},
//        [TOKEN_OR]              = {NULL,     NULL,   PREC_NONE},
        [TOKEN_OR]              = {NULL,     or_,    PREC_OR},
        [TOKEN_PRINT]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_RETURN]          = {NULL,     NULL,   PREC_NONE},
        [TOKEN_SUPER]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_THIS]            = {NULL,     NULL,   PREC_NONE},
//        [TOKEN_TRUE]            = {NULL,     NULL,   PREC_NONE},
        [TOKEN_TRUE]            = {literal,  NULL,   PREC_NONE},
        [TOKEN_VAR]             = {NULL,     NULL,   PREC_NONE},
        [TOKEN_WHILE]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_ERROR]           = {NULL,     NULL,   PREC_NONE},
        [TOKEN_EOF]             = {NULL,     NULL,   PREC_NONE},
};

static void parsePrecedence(Precedence precedence) {
    // ?
    advance();
    ParseFn prefixRule = getRule(parser.previous.type)->prefix;
    if (prefixRule == NULL) {
        error("Expect expression");
        return;
    }

//    prefixRule();
    bool canAssign = precedence <= PREC_ASSIGNMENT;
    prefixRule(canAssign);

    while (precedence <= getRule(parser.current.type)->precedence) {
        advance();
        ParseFn infixRule = getRule(parser.previous.type)->infix;
//        infixRule();
        infixRule(canAssign);
    }

    if (canAssign && match(TOKEN_EQUAL)) {
        error("Invalid assignment target.");
    }
}

static ParseRule* getRule(TokenType type) {
    return &rules[type];
}


//void compile(const char* source) {
//bool compile(const char* source, Chunk* chunk) {
ObjFunction* compile(const char* source) {
    initScanner(source);
//    int line = -1;
//    for (;;) {
//        Token token = scanToken();
//        if (token.line != line) {
//            printf("%4d ", token.line);
//            line = token.line;
//        } else {
//            printf("    | ");
//        }
//        printf("%2d '%.*s'\n", token.type, token.length, token.start);
//
//        if (token.type == TOKEN_EOF) break;
//    }
    Compiler compiler;
//    initCompiler(&compiler);
//    compilingChunk = chunk;
    initCompiler(&compiler, TYPE_SCRIPT);

    parser.hadError = false;
    parser.panicMode = false;

    advance();

//    expression();
//    consume(TOKEN_EOF, "Expect end of expression.");
    while (!match(TOKEN_EOF)) {
        declaration();
    }

//    endCompiler();
    ObjFunction* function = endCompiler();
//    return !parser.hadError;
    return parser.hadError ? NULL : function;
}