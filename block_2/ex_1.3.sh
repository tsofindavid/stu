mkdir -p ./dist
rm -rf ./dist/ex_1.3
gcc ex_1.3.c -masm=intel -o ./dist/ex_1.23
chmod +x ./dist/ex_1.3
./dist/ex_1.3