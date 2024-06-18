#!/bin/bash
BUILD="build"
MATERIALS="${BUILD}/materials"

YELLOW="\033[1;33m"
GREEN="\033[1;32m"
RED="\033[1;31m"
NOCOLOR="\033[0m"

mkdir -p $MATERIALS

echo -e "${YELLOW}Compiling strarr${NOCOLOR}"
gcc -c strarr.c -o "${MATERIALS}/strarr.o"

echo -e "${YELLOW}Compiling seed${NOCOLOR}"
gcc -c seed.c -o "${MATERIALS}/seed.o"

echo -e "${YELLOW}Compiling readstream${NOCOLOR}"
gcc -c readstream.c -o "${MATERIALS}/readstream.o"

echo -e "${YELLOW}Compiling split${NOCOLOR}"
gcc -c split.c -o "${MATERIALS}/split.o"

echo -e "${YELLOW}Compiling main${NOCOLOR}"
gcc "${MATERIALS}/strarr.o" "${MATERIALS}/seed.o" "${MATERIALS}/readstream.o" "${MATERIALS}/split.o" main.c -o "${BUILD}/random"

if [ $? -eq 0 ]; then
	echo -e "${GREEN}Done!${NOCOLOR}"
	echo "The program should be in ${BUILD}/random"
else
	echo -e "${RED}Failed to compile :c${NOCOLOR}"
fi
