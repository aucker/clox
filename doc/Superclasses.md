# Superclasses

## Inheriting Methods

Lox inheritance syntax looks like this:
```shell
class Doughnut {
  cook() {
    print "Dunk in the fryer.";
  }
}

class Cruller < Doughnut {
  finish() {
    print "Glaze with icing.";
  }
}
```

Here, the Cruller class inherits from Doughnut and thus, instances of Cruller inherits the `cook()` method. 

### Executing inheritance

### Invalid superclasses

Our implementation is simple and fast, which is just the way I like my VM code. But it's not robust. Nothing prevents a
user from inheriting from an object that isn't a class at all:
```shell
var NotClass = "So not a class.";
class OhNo < NotClass {}
```

## Storing Superclasses

Did you notice that when we added method inheritance, we didn't actually add any reference from a subclass to its 
subclass? After we copy the inherited methods over, we forget the superclass entirely. We don't need to keep a handle on
the superclass, so we don't.

That won't be sufficient to support super calls. Since a subclass may override the superclass method, we need to be able
to get our hands on superclass method tables. Before we get to that mechanism, I want to refresh your memory on how 
super calls are statically resolved.

### A superclass local variable

Our compiler already emits code to load the superclass onto the stack. Instead of leaving that slot as a temporary, we
create a new scope and make it a local variable.

