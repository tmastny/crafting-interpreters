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

# chapter-26_a

This example does not garbage collect:
```js
var a = "hello";
a = "world!";
// gc
print a;
```

Reason:
- the compiler stores both string literals in the `<script>`
  function's chunk constant array.
- The compiler function is explicitly marked
- The compiler also returns the function and it becomes the first
  variable on the VM stack.
  - anything on the VM stack is marked.
