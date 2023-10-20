# Jumping Back and Forth

## If Statement

First, we compile the condition expression, bracketed by parentheses. At runtime, that will leave the condition value on 
top of the stack. We'll use that to determine whether to execute the then branch or skip it.

> Have you ever noticed that the `(` after the `if` keyword doesn't actually do anything useful? The language would be 
> just as unambiguous and easy to parse without it, like:
> `if condition) print ("looks weird");`
> The closing `)` is useful because it separates the condition expression from the body. Some language uses a `then` 
> keyword instead. But the opening `(` doesn't do anything. It's just there because unmatched parentheses look bad to us
> humans.

Then we emit a new `OP_JUMP_IF_FALSE` instruction. It has an operand for how much to offset the `ip` - how many bytes of
code to skip. If the condition is falsey, it adjusts the `ip` by that amount. Something like this:
![or_jump_if_false](../pic/OR_JUMP_IF_FALSE.png)
But we have a problem. When we're writing the `OP_JUMP_IF_FALSE` instruction's operand, how do we know how far to jump?
We haven't compiled the then branch yet, so we don't know how much bytecode it contains.

To fix that, we use a classic trick called **backpatching**. We emit the jump instruction first with a placeholder 
offset operand. We keep track of where that half-finished instruction is. Next, we compile the then body. Once that's 
done, we know how far to jump. So we go back and replace that placeholder offset with the real one now that we can 
calculate it. Sort of like sewing a patch onto the existing fabric of the compiled code.
![backpatching](../pic/backpatching.png)


After reading the offset, we check the condition value on top of the stack. If it's falsey, we apply this jump offset to
the `ip`. Otherwise, we leave the `ip` alone and execution will automatically proceed to the next instruction following 
the jump instruction.

In the case where the condition is falsey, we don't need to do any other work. We've offset the `ip`, so when the outer
instruction dispatch loop turns again, it will pick up execution at that new instruction, past all the code in then 
branch.

Note that the jump instruction doesn't pop the condition value off the stack. So we aren't totally done here, since this
leaves an extra value floating around on the stack. We'll clean that up soon. Ignoring that for the moment, we do have 
a working `if` statement in Lox now, with only one little instruction required to support it at runtime in the VM.

