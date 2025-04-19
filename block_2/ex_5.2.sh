mkdir -p ./dist
rm -rf ./dist/ex_5.2
gcc ex_5.2.c -lncurses -Wno-format-security -o ./dist/ex_5.2 
chmod +x ./dist/ex_5.2 
./dist/ex_5.2 