#!/usr/bin/env bash

# Clean up the display
reset

export CC=/usr/bin/gcc
export CXX=/usr/bin/g++

# Current Working Directory
CURRENTDIRECTORY=`pwd`

# Clean up the older build directory
rm -rf build

# Create a new build directory
mkdir build

# Enter the build directory
cd build

# Run cmake
#cmake --debug-output ..
#cmake --trace-expand ..
cmake ..

# Run Make
make

# Execute Main
echo
echo
echo "Running Main..."
echo
echo
./main

# Memory analysis 
# valgrind --tool=massif --trace-children=yes --detailed-freq=1 --vgdb=full --track-fds=yes --read-inline-info=yes --read-var-info=yes --heap=yes --stacks=yes ./main
# valgrind --leak-check=full --num-callers=20 --trace-children=yes --tool=memcheck ./main
