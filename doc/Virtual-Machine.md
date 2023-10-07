# A Virtual Machine

> Magicians protect their secrets not because the secrets are large and important, but because they are so small and 
> trivial. The wonderful effects created on stage are often the result of a secret so absurd that the magician would be
> embarrassed to admit that that was how it was done.
> - Christopher Priest, *The Prestige*

## An Instruction Execution Machine

The virtual machine is one part of our interpreter's internal architecture. You hand it a chunk of code - literally a 
Chunk - and it runs it.

> The choice to have a static VM instance is a concession for the book, but not necessarily a sound engineering choice
> for a real language implementation. If you're building a VM that's designed to be embedded in other host applications,
> it gives the host more flexibility if you *do* explicitly take a VM pointer and pass it around.
> 
> That way, the host app can control when and where memory for the VM is allocated, run multiple VMs in parallel, etc.

### *Executing instructions*

The name "IP" is traditional, and - unlike many traditional names in CS - actually makes sense: it's an [instruction 
pointer](https://en.wikipedia.org/wiki/Program_counter). Almost every instruction set in the world, real and virtual, 
has a register or variable like this.

### *Execution tracing*

If you run clox now, it executes the chunk we hand-authored in the last chpater and spits out `1.2` to terminal. We can 
see that it's working, but that's only because our implementation of `OP_CONSTANT` has temporary code to log the value.
Once that instruction is doing what it's supposed to do and plumbing that constant along to other operations that want 
to consume it, the VM will become a black box. That makes our lives as VM implementer harder.

To help ourselves out, now is a good time to add some diagnostic logging to the VM like we did with chunks themselves. 
In fact, we'll even reuse the same code. We don't want this logging enabled all the time - it's just for us VM hackers, 
not Lox users - so first we create a flag to hide it behind.

