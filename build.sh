#!/bin/bash

clear

if [ -d build ] ; then
	echo -e "\033[0;33m[!] Found previous build folder, deleting...\033[0m"
	rm -rf build
fi

mkdir build
cd build

cmake ..
cmake --build .
cmake --build . --target run
cmake --build . --target clean
cmake --build . --target extra_clean

cd .. 
rm -rf build
