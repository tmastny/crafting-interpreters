gcc clox/*.c

echo "Without register:" >> README.md
./a.out clox/clock.lox >> README.md


gcc clox-register/*.c
echo "With register:" >> README.md
./a.out clox/clock.lox >> README.md
