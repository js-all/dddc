gcc -Wall -c -lm ./matrixs.c
gcc -Wall -c -lm ./main.c
gcc -o a -lm ./matrixs.o ./main.o
rm ./*.o
chmod +x a
./a
