gcc -c str_vec.c -o str_vec.o
gcc -c seed.c -o seed.o
gcc main.c str_vec.o seed.o -o random
