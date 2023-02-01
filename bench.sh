gcc clox/*.c

echo "Without closure:" >> README.md
./a.out clox/clock.lox >> README.md


gcc clox-standard/*.c
echo "With closure:" >> README.md
./a.out clox/clock.lox >> README.md
