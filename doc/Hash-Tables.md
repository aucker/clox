# Hash Tables

## String Interning

The reason the hash table doesn't totally work is that when `findEntry()` checks to see if an existing key matches the
one it's looking for, it uses `==` to compare two strings for equality. That only returns true if the two keys are the 
exact same string in memory. Two separate strings with the same characters should be considered equal, but aren't.

Back when we added strings in the last chapter, we added explicit support to compare the strings character-by-character 
to get true equality. We could do that for `findEntry()`, but that's slow.

Instead, we'll use a technique called **string interning**. The core problem is that it's possible to have different 
strings in memory with the same characters. Those need to behave like equivalent values even though they are distinct 
objects. They're essentially duplicates, and we have to compare all of their bytes to detect that.

String interning is a process of deduplication. We create a collection of "interned" strings. Any string in that 
collection is guaranteed to be textually distinct from all others. When you intern a string, you look for a matching 
string in the collection. If found, you use that original one. Otherwise, the string you have is unique, so you add it 
to the collection.

In this way, each sequence of characters is represented by only one string in memory. This makes value equality trivial.
If two strings point to the same address in memory, they are obviously the same string and must be equal. And, because 
we know strings are unique, if two strings point to different addresses, they must be distinct strings.


## Conclusion

We've add a little overhead when creating strings to intern them. But in return, at runtime, the equality operator on 
strings is much faster. With that, we have a full-featured hash table ready to use for tracking variables, instances, or 
any other k/v pairs that might show up.

We also sped up testing strings for equality. This is nice for when the user does `==` on strings. But it's even more 
critical in a dynamically typed language like Lox where method calls and instance fields are looked up by name at 
runtime.
If testing a string for equality is slow, then that means looking up a method by name is slow. And if *that's* slow in
your object-oriented language, then *everything* is slow.