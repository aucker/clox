# Clox ⚙

A Lox Interpreter implemented by C.

## Usage

```bash
mdkir build && cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON . // optional
cmake -DCMAKE_BUILD_TYPE=DEBUG ..  // optional
ln -s build/compile_commands.json compile_commands.json // optional
cmake .. && make
./clox
```

And you will get a REPL of Lox.
