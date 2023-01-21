# Chapter 21

```
> var a = 1; a = 1; print a;
== code ==
0000    1 OP_CONSTANT         1 '1'
0002    | OP_DEFINE_GLOBAL    0 'a'
0004    | OP_CONSTANT         3 '1'
0006    | OP_SET_GLOBAL       2 'a'
0008    | OP_POP
0009    | OP_GET_GLOBAL       4 'a'
0011    | OP_PRINT
0012    2 OP_RETURN

0000    1 OP_CONSTANT         1 '1'
          [ 1 ]
0002    | OP_DEFINE_GLOBAL    0 'a'

0004    | OP_CONSTANT         3 '1'
          [ 1 ]
0006    | OP_SET_GLOBAL       2 'a'
          [ 1 ]
0008    | OP_POP

0009    | OP_GET_GLOBAL       4 'a'
          [ 1 ]
0011    | OP_PRINT
1

0012    2 OP_RETURN
```

# Chapter 21 Exercise 1

```
> var a = 1; a = 1; print a =1;
---> in makeConstant. Constants:
---> in makeConstant. Constants: a,
---> in makeConstant. Constants: a, 1,
---> in makeConstant. Constants: a, 1, 1,
```
