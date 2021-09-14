# `c::file`

`c::file` is a `FILE*` wrapper. It handles basic file operations.


## member types

| Type 				| Description |
| --- 					| --- |
| `mode` | Describes the way a file will be opened. These are exclusive and cannot be OR-ed together. |

## member functions

| Function 				| Description |
| --- 					| --- |
| `(destructor)`		| Closes the file if it's open. |
| `open` *(static)*		| Opens the specified file in the specified `file::mode`. Be aware that the return type is `err<file>`. Operates like `fopen`. |
| `close` 				| Closes the file if it's open. |
| `is_valid` 			| Whether the file is open. |
| `file_mode` 			| Which `file::mode` this file was opened in. |
