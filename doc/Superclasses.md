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
