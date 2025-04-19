mkdir -p ./dist
rm -rf ./dist/ex_5.1
gcc ex_5.1.c -lncurses -Wno-format-security -o ./dist/ex_5.1
chmod +x ./dist/ex_5.1
./dist/ex_5.1