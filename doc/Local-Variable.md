# Local Variable

## Representing Local Variables

Our compiler has the data it needs, but not the operations on that data. There's no way to create and destroy scopes, 
or add and resolve variables. We'll add those as we need them. First, let's start building some language features.

## Block Statements

Before we can have any local variables, we need some local scopes. These come from two things: function bodies and 
blocks. Functions are a big chunk of work that we'll tackle in a later chapter, so for now we're only going to do 
blocks. As usual, we start with the syntax. The new grammar we'll introduce is:
```shell
statement     -> exprStmt
               | printStmt
               | block ;
               
block         -> "{" declaration* "}" ;             
```
> When you think about it, "block" is a weird name. Used metaphorically, "block" usually means a small indivisible unit,
> but for some reason, the Algol 60 committee decided to use it to refer to a *compound* structure - a series of 
> statements. It could be worse, I suppose. Algol 58 called `begin` and `end` "statement parentheses".

