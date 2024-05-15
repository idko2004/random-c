echo "Compiling strarr"
gcc -c strarr.c -o build/materials/strarr.o

echo "Compiling seed"
gcc -c seed.c -o build/materials/seed.o

echo "Compiling main"
gcc main.c build/materials/strarr.o build/materials/seed.o -o build/random

if [ $? -eq 0 ]; then
	echo "Done!"
else
	echo "Failed to compile :c"
fi
