mkdir -p ./dist
rm -rf ./dist/ex_1.2
gcc ex_1.2.c -masm=intel -o ./dist/ex_1.2
chmod +x ./dist/ex_1.2
./dist/ex_1.2