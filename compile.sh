gcc -g -Wall -c -lm ./matrixs.c
gcc -g -Wall -c ./vectors.c
gcc -g -Wall -c -lm ./main.c
gcc -g -o a -lm ./matrixs.o ./vectors.o ./main.o
rm ./*.o
chmod +x a
./a
