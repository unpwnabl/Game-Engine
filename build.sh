#!/usr/bin/env bash

if [[ $# -ge 1 ]] ; then 
	case "${1:-}" in
		"--help" | "-h")
			echo -e "Usage:\n\t./build.sh [options]\nGeneral options:\n\t-h, --help\t\t\tShow help\n\t-svexe\t\t\t\tCreate a dir/ folder with the exe\n\t\t\t\t\tand subsequent dependencies\n\t<no opts>\t\t\tJust build and run"
			exit
			;;
		"-svexe")
			;;
		*)
			echo -e "\033[0;31m[✗] Wrong argument passed, please use \"--help\" or \"-h\" to view help page\033[0m"
			exit
	esac
fi

clear

# In case we didn't destroy them while cleaning up
if [ -d build ] ; then
	echo -e "\033[0;33m[!] Found previous build folder, deleting...\033[0m"
	rm -rf build
fi
if [ -d dist ] ; then
	echo -e "\033[0;33m[!] Found previous distribution folder, deleting...\033[0m"
	rm -rf dist
fi

mkdir build
cd build

cleanup() {
	cd .. 
	rm -rf build
}
# Make sure no matter how we exit, we do clean up
trap cleanup EXIT

cmake ..
cmake --build .
cmake --build . --target run
if [[ "${1:-}" == "-svexe" ]] ; then
	echo -e "\033[0;33m[!] Creating permanent build inside dist/ \033[0m"
	cmake --build . --target bundle
fi
cmake --build . --target clean
cmake --build . --target extra_clean

