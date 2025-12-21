clear

mkdir build
cd build

cmake ..
cmake --build .
cmake --build . --target run
cmake --build . --target clean
cmake --build . --target extra_clean

cd .. 
rm -rf build
