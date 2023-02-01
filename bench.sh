gcc clox/*.c

echo "With type checking:" >> README.md
./a.out clox/clock.lox >> README.md


gcc clox-standard/*.c
echo "Without type checking:" >> README.md
./a.out clox/clock.lox >> README.md
