Lox Grammar, v1:
```
expression     → literal
               | unary
               | binary
               | grouping ;

literal        → NUMBER | STRING | "true" | "false" | "nil" ;
grouping       → "(" expression ")" ;
unary          → ( "-" | "!" ) expression ;
binary         → expression operator expression ;
operator       → "==" | "!=" | "<" | "<=" | ">" | ">="
               | "+"  | "-"  | "*" | "/" ;
```

# Representing Code - Challenge 1
expr -> expr other
expr -> IDENTIFIER
expr -> NUMBER

expr -> "()"
expr -> "("

other -> "(" ( expr    ( "," expr )*     )?      ")"
other -> "(" ( expr ( "," expr )* )? ")" other

other -> "." IDENTIFIER
other -> "." IDENTIFIER other

--
list -> "()"
list -> "(" item ")"
list -> "(" item ")" method

method -> "." IDENTIFIER
method -> "." IDENTIFIER method

item -> IDENTIFIER
item -> IDENTIFIER "," item
item -> NUMBER
item -> NUMBER "," item
