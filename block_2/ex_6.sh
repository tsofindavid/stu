mkdir -p ./dist
rm -rf ./dist/ex_6
gcc ex_6.c -lncurses -Wno-format-security -o ./dist/ex_6
chmod +x ./dist/ex_6
./dist/ex_6