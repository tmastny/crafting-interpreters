# hash tables

## support for other types

Numbers, Bools, and Nils are Value type, not Obj, so it's not as
straightforward to extend the key to be any Obj.

Numbers
- double type
  - cast to integer and save at that index?
    - would work if keys were distributed amoungst integers, but would fail
      over a sequence of values within a small range like 0.234, 0.99, etc.
  - hash the byte value of the double

Bool
- bool type
  - If we cast to integer, how to distinguish between 1 `number` and 1 `true`?
    - if we hash `(double)1`, it will be a different value than `(int)true`,
      because the byte structure of double is different

## uint32_t as key

If I change the interface to directly take the `uint32_t` has, how can I still
use the `interned` string interface?

## Strings as key

What if we serialized Numbers, Bools, and Nils as `ObjString`?
To avoid collisions, we would need to prefix the string by something
the user wouldn't want to hash.
- `__loxKey__<serialized-value>`

### String struct as key
Alternatively, what if I use the `ObjString` as an interface, but only
fill in the `hash` for the data type?

So if I wanted to hash `1.1` I would call

```c
// wrap in makeValueKey
Value value = NUMBER_VAL(1.1);
ObjString* key = allocateString(NULL, 0, doubleHash(value));
tableSet(table, key, value);
```

## Python `hash`

Some Python hash inspira:

```python
>>> hash(1)
1
>>> hash(1.1)
230584300921369601
>>> hash(True)
1
>>> hash(None)
273837127
>>> {1: 1, True: 1}
{1: 1}
```
