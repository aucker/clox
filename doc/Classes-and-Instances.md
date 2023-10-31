# Classes and Instances

## Class Objects

In a class-based object-oriented language, everything begins with classes. They define what sorts of objects exist in 
the program and are the factories used to produce new instances. Going bottom-up, we'll start with their runtime 
representation and then hook that into the language.

## Class Declarations

Runtime representation in hand, we are ready to add support for classes to the language. Next, we move into the parser.


> "Local" classes - classes declared inside the body of a function or block, are an unusual concept. Many Lang don't 
> allow them at all. But since Lox is a dynamically typed scripting language, it treats the top level of a program and 
> the bodies of functions and blocks uniformly. Classes are just another kind of declaration, and since you can declare
> variables and functions inside blocks, you can declare classes in there too.

## Instances of Classes

Classes serve two main purposes in a language:
* **They are how you create new instances**. Sometimes this involves a `new` keyword, other times it's a method call on
    the class object, but you usually mention the class by name *somehow* to get a new instance.
* **They contain methods**. These define how all instances of the class behave.

