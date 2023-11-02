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

> The VM trusts that the instructions it executes are valid bc the *only* way to get code to the bytecode interpreter is
> by going through clox's own compiler. Many bytecode VMs, like the JVM and CPython, support executing bytecode that has
> been compiled separately. That leads to a different security story. Maliciously crafted bytecode could crash the VM or
> worse.
> 
> To prevent that, the JVM does a bytecode verification pass before it executes and loaded code. CPython says it's up to
> the user to ensure any bytecode they run is safe.


## Method References

Most of the time, methods are accessed and immediately called, leading to this familiar syntax:
```shell
instance.method(argument)
```
But remember, in Lox and some other languages, those two steps are distinct and can be separated.
```shell
var closure = instance.method;
closure(argument);
```

Since users *can* separate the operations, we have to implement them separately. The first step is using our existing 
dotted property syntax to access a method defined on the instance's class. That should return some kind of object that
the user can then call like a function.

The obvious approach is to look up the method in the class's method table and return the ObjClosure associated with that
name. But we also need to remember that when you access a method, `this` gets bound to the instance the method was 
accessed from. In jlox, we added methods like this:
```shell
class Person {
  sayName() {
    print this.name;
  }
}

var jane = Person();
jane.name = "Jane";

var method = jane.sayName;
method();
```

This should print "Jane", so the object returned by `.sayName` somehow needs to remember the instance it was accessed 
from when it later gets called. In jlox, we implemented that "memory" using the interpreter's existing heap-allocated
Environment class, which handled all variable storage.

Our bytecode VM has a more complex architecture for storing state. Local variables and temporaries are on the stack,
globals are in a hash table, and variables in closures use upvalues. That necessitates a somewhat more complex solution
for tracking a method's receiver in clox, and a new runtime type.

### Bound methods

When the user executes a method access, we'll find the closure for that method and wrap it in a new "bound method" 
object that tracks the instance that the method was accessed from. This bound object can be called later like a 
function. When invoked, the VM will do some shenanigans to wire up `this` to point to the receiver inside the method's 
body.

> The name "bound method" is from CPython, Python behaves similar to Lox here, and I used it implementation for 
> inspiration.


### Accessing methods

Let's get our new object type doing something. Methods are accessed using the same "dot" property syntax we implemented
in the last chapter. The compiler already parses the right expressions and emits `OP_GET_PROPERTY` instructions for 
them. The only changes we need to make are in the runtime.

When a property access instruction executes, the instance is on top of the stack. The instruction's job is to find a 
field or method with the given name and replace the top of the stack with the accessed property.

The interpreter already handles fields, so we simply extend the `OP_GET_PROPERTY` case with another section.

E.g.:
```shell
class Brunch {
  eggs() {}
}

var brunch = Brunch();
var eggs = brunch.eggs;
```
Here is what happens when the VM executes the `bindMethod()` call for the `brunch.eggs` expression:

![VM bindMethod](../pic/VM-bindMethod.png)

That's a lot of machinery under the hood, but from the user's perspective, they simply get a function that they can 
call.
