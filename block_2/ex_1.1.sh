mkdir -p ./dist
rm -rf ./dist/ex_1.1
gcc ex_1.1.c -masm=intel -o ./dist/ex_1.1
chmod +x ./dist/ex_1.1
./dist/ex_1.1