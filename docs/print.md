# `c::print`

`c::print_*` is a group of simple variadic template functions to print an arbitrary amount of strings to `stdout`.

## Functions

| Function 			| Description |
| --- 				| --- |
| `print_error`		| Prints the message with `(error)` prepended. |
| `print_debug` 	| Prints the message with `(debug)` prepended, and only in debug builds (with `NDEBUG` not defined). (the latter is not implemented at the moment)|