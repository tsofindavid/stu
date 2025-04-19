mkdir -p ./dist
rm -rf ./dist/ex_4
gcc ex_4.c -lncurses -Wno-format-security -lao -ldl -lm -o ./dist/ex_4
chmod +x ./dist/ex_4
./dist/ex_4