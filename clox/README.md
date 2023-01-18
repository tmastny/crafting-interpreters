Expression:
```c
(-1 + 2) * 3 - -4
```

Trace:
```c
parsePrecedence(PERC_ASSIGN);
  grouping(),prefix,expression,parsePrecedence(PERC_ASSIGN)
    unary(), prefix
      unary(), number, prefix
      precedence [PERC_UNARY] !< precedence [PERC_TERM]
    precedence [PERC_ASSIGN] < precedence [PERC_TERM]
      binary(), infix
        parsePrecedence(PERC_TERM + 1 aka PERC_FACTOR)
        number(),prefix
        precedence [PERC_FACTOR] !< precedence [PERC_NONE from `)`]
      addbinaryop
    precedence [PERC_ASSIGN] !< precedence [PERC_NONE from `)`]
  in grouping(), consume(`)`)
  precedence [PERC_ASSIGN] !< precedence [PERC_FACTOR from `*`]
    binary(), infix
      parsePrecedence(PERC_FACTOR + 1 aka PREC_UNARY)
        number(), prefix
        precedence [PREC_UNARY] !< precedence [PERC_TERM from `-`]
    addbinaryop
  precedence [PERC_ASSIGN] !< precedence [PERC_FACTOR from `-`]
    binary(), infix
      parsePrecedence(PERC_FACTOR + 1 aka PERC_TERM)
        unary(), prefix
          unary(), number
          precedence [PERC_NONE] !< precedence [PERC_NONE from `EOF`]
        precedence [PERC_UNARY] !< precedence [PERC_NONE from `EOF`]
    addbinaryop
```

Debug output:
```
0000    1 OP_CONSTANT         0 '1'
          [ 1 ]
0002    | OP_NEGATE
          [ -1 ]
0003    | OP_CONSTANT         1 '2'
          [ -1 ][ 2 ]
0005    | OP_ADD
          [ 1 ]
0006    | OP_CONSTANT         2 '3'
          [ 1 ][ 3 ]
0008    | OP_MULTIPLY
          [ 3 ]
0009    | OP_CONSTANT         3 '4'
          [ 3 ][ 4 ]
0011    | OP_NEGATE
          [ 3 ][ -4 ]
0012    | OP_SUBTRACT
          [ 7 ]
0013    2 OP_RETURN
7
```
