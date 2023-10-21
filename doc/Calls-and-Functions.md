# Calls and Functions

## Function Objects

The most interesting structural change in the VM is around the stack. We already *have* a stack for local variables and 
temporaries, so we're partway there. But we have no notion of a *call* stack. Before we can make much progress, we'll 
have to fix that. But first, let's write some code. We can't do much without having any kinds of representation for 
functions, so we'll start there. From the VM's perspective, what is a function?

A function has a body that can be executed, so that means some bytecode. We could compile the entire program and all of 
its function declarations into one big monolithic Chunk. Each function would have a pointer to the first instruction of
its code inside the Chunk.

This is roughly how compilation to native code works where you end up with one solid blob of machine code. But for our 
bytecode VM, we can do something a little higher level. I think a cleaner model is to give each function its own Chunk.
We'll want some other metadata too, so let's go ahead and stuff it all in a struct now.


## Compiling to Function Objects

Right now, our compiler assumes it is always compiling to one single chunk. With each function's code living in separate
chunks, that gets more complex. When the compiler reaches a function declaration, it needs to emit code into the 
function's chunk when compiling its body. At the end of the function body, the compiler needs to return to the previous
chunk it was working with.

That's fine for code inside function bodies, but what about code that isn't? The "top level" of a Lox program is also 
imperative code and we need a chunk to compile that into. We can simplify the compiler and VM by placing that top-level
code inside an automatically defined function too. That way, the compiler is always within some kind of function body,
and the VM always runs code by invoking a function. It's as if the entire program is wrapped inside an implicit `main()`
function.



We get the function object from the compiler. If there were no compiler errors, we return it. Otherwise, we signal an 
error by returning `NULL`. This way, the VM doesn't try to execute a function that may contain invaild bytecode.

Eventually, we will update `interpret()` to handle the new declaration of `compile()`, but first we have some other 
changes to make.

