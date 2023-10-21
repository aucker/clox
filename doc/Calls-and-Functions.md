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

