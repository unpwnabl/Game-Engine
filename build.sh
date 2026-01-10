#!/usr/bin/env bash

if [[ "${1:-}" == "--help" ]] || [[ "${1:-}" == "-h" ]] ; then
	echo -e "Usage:\n\t./build.sh [options]\nGeneral options:\n\t-h, --help\t\t\tShow help\n\t-svexe\t\t\t\tCreate a dir/ folder with the exe\n\t\t\t\t\tand subsequent dependencies"
	exit
fi

clear

if [ -d build ] ; then
	echo -e "\033[0;33m[!] Found previous build folder, deleting...\033[0m"
	rm -rf build
fi
if [ -d dist ] ; then
	echo -e "\033[0;33m[!] Found previous bundle folder, deleting...\033[0m"
	rm -rf dist
fi

mkdir build
cd build

cmake ..
cmake --build .
cmake --build . --target run
if [[ "${1:-}" == "-svexe" ]] ; then
	echo -e "\033[0;33m[!] Creating permanent build inside dir/ \033[0m"
	cmake --build . --target bundle
fi
cmake --build . --target clean
cmake --build . --target extra_clean

cd .. 
rm -rf build
