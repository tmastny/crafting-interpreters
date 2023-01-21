`let` works with local variables, but not with global on this branch.

In the compiler, globals are saved as string constants and then `OP_SET_GLOBAL`
looks up the value by name in the hash table.

Therefore, there is no compile-time object that creates a global variable
like this is for local (the `Local` struct).

With `Local`, during compile-time, we can check whether it was declared with `let`
or `var`. And then during any assignment operations on that variable, we can
check if it is `assignable`.

We would need to create a more generalized variable struct to use with global
and locals that declare if it is assignment during compile time.
