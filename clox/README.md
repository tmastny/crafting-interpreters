Current garbage collection bug. During compilation,
any allocate triggers collection of the top-level
"script" function.

For example, the program:
```
> 1;
```
triggers a collection on
```
compiler->function
```
via

```
(lldb) print function
(ObjFunction *) $0 = 0x0000000100404080

(lldb) print current->function
(ObjFunction *) $1 = 0x0000000100404080
```

But this function should be marked in
`markCompilerRoots()`, but for some
reason it's not.
- Ah, turns out I was marking the enclosing
  rather than the function

Also interesting to note:
- garbage collection does not free dangling strings
  in the global namespace: https://github.com/munificent/craftinginterpreters/issues/1068

^ example mislead me for a few reasons.
1. constants are never collected, because they are generated at
   compile time in the `<script>` function, which is always marked.
2. In the current design, `gc` would never be called between those two
   lines (although it could), because `gc` is called only during
   allocations.

# Collecting a closure

Closure script example.

`OP_CLOSURE` creates a new closure on the stack
`OP_SET_GLOBAL` binds the closure to the variable `c`.
- during Garbage collection, the variable name `c` and the
  value closure are marked in `markTable`.

Next, calling `makeCounter` brings about a new `OP_CLOSURE`,
creating a new closure.
Once again, `OP_SET_GLOBAL` binds `c` to the new closure.
The old closure is `dangling` (no variable in lox references it).

A new object is allocated, so garbage collection is called.
The new garbage collection marks all the global names and value
and doesn't find the first `OP_CLOSURE`.

`OP_CLOSURE` and it's up value are then eliminated when walking the all objects linked
list.
- upValue 1, closure
- (see line 824)
