# `c::err`

`c::err` is a "maybe"/"optional" type with an error message. This is the main way that `c_ext` deals with errors. Exceptions are only used if this type is mistreated.
