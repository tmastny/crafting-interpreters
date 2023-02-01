I think you need to create a new object `ObjCallable`
that is has all the fields of `ObjFunction` and
`ObjClosure`, with a field to indicate whether the
function is a closure.

Otherwise, `vm.c` gets very complicated:
- each frame requires a closure object to manage
  the code chunks. That could be a function _or_
  closure object, so we either need to type check
  or have an object that works for both.
- but unless you duplicate a lot of code, the
  type checker doesn't like `FRAME_CALLABLE()`
