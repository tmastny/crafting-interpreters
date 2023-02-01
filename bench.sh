gcc clox/*.c

echo "With register:" >> README.md
./a.out clox/clock.lox >> README.md


gcc clox-standard/*.c
echo "Without register:" >> README.md
./a.out clox/clock.lox >> README.md
