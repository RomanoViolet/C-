#!/usr/bin/env bash

# Clean up the display
reset

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

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
cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. # exports compile options for use with cppcheck

# Run Make
make

# Execute Main
echo
echo
echo "Running myProject..."
echo
echo
./myProject

# Run profilers only on release builds
BUILDTYPE="$(grep ./CMakeCache.txt -e 'CMAKE_BUILD_TYPE:STRING')"
[[ $BUILDTYPE =~ =(.*)$ ]]
BUILDTYPE=${BASH_REMATCH[1]}
if [[ ${BUILDTYPE} == "RELEASE" ]]; then
    valgrind --tool=massif --trace-children=yes --detailed-freq=1 ./myProject
    valgrind --leak-check=full --num-callers=20 --trace-children=yes --tool=memcheck ./myProject
    valgrind --tool=DRD --vgdb=yes --leak-check=full --num-callers=20 --trace-children=yes --tool=memcheck --show-leak-kinds=all --track-origins=yes --track-fds=yes ./myProject

    # Run CPP Check. Runs unconditionally
    cppcheck --project=./compile_commands.json --enable=all --std=c++11 --std=posix --verbose
fi

