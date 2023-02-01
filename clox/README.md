* Added forward declaration of `runtimeError` so
  native functions can call it.

* in `run`, passed in a bool pointer to be set
  if a `runtimeError` occurs. Then returns false
  which `OP_CALL` in `run` returns as an `INTERPRET_RUNTIME_ERROR`
