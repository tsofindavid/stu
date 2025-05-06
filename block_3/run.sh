mkdir -p ./dist
rm -rf ./dist/client
gcc client.c  -o ./dist/client
chmod +x ./dist/client
./dist/client