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
