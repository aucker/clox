# Methods and Initializers

It is time for our VM to bring its nascent objects to life with behavior. That means methods and method calls. And, 
since they are a special kind of method, initializers too.

All this is familiar territory from our previous jlox interpreter. What's new in this second trip is an important 
optimization we'll implement to make method calls over seven times faster than our baseline performance. But before we
get to that fun, we gotta get the basic stuff working.

## Method Declarations

### Representing methods

We use the existing `markTable()` function, which traces through the key string and value in each table entry.

Storing a class's methods is pretty familiar coming from jlox. The different part is how that table gets populated. Our
previous interpreter had access to the entire AST node for the class declaration and all the methods it contained. At 
runtime, the interpreter simply walked that list of declarations.

Now every piece of information the compiler wants to shunt over to the runtime has to squeeze through the interface of a
flat series of bytecode instructions. 

### Compiling method declarations

Lox doesn't have field declarations, so anything before the closing brace at the end of the class body must be a method.
We stop compiling methods when we hit that final curly or if we reach the end of the file. The latter check ensures our
compiler doesn't get stuck in an infinite loop if the user accidentally forgets the closing brace.

The tricky part with compiling a class declaration is that a class may declare any number of methods. Somehow the 
runtime needs to look up and blind all of them. That would be a lot to pack into a single `OP_CLASS` instruction. 
Instead, the bytecode we generate for a class declaration will split the process into a *series* of instructions. The 
compiler already emits an `OP_CLASS` instruction that creates a new empty ObjClass object. Then it emits instructions to
store the class in a variable with its name.

Now, for each method declaration, we emit a new `OP_METHOD` instruction that adds a single method to that class. When 
all the `OP_METHOD` instructions have executed, we're left with a fully formed class. While the user sees a class 
declaration as a single atomic operation, the VM implements it as a series of mutations.

> We did something similar for closures. The `OP_CLOSURE` instruction needs to know the type and index for each 
> captured upvalue. We encoded that using a series of pseudo-instructions following the main `OP_CLOSURE` instruction - 
> basically a variable number of operands. The VM processes all of those extra bytes immediately when interpreting the
> `OP_CLOSURE` instruction.
> 
> Here our approach is a little different bc from the VM's perspective, each instruction to define a method is a 
> separate stand-alone operation. Either approach would work. A variable-sized pseudo-instruction is possibly marginally
> faster, but class declarations are rarely in hot loops, so it doesn't matter much.

To define a new method, the VM needs three things:
1. The name of the method.
2. The closure for the method body.
3. The class to bind the method to.

We'll incrementally write the compiler code to see how those all get through to the runtime.