#!/usr/bin/env bash
project_root=$(pwd)
echo "project_root: ${project_root}"
if [[ -d "${project_root}/../build/negative-compiler-tests" ]]
then
    rm -rf ${project_root}/../build/negative-compiler-tests
fi

mkdir ${project_root}/../build/negative-compiler-tests
cp -r ./NegativeCompilerTests.cpp ./*.hpp ${project_root}/../build/negative-compiler-tests/
rm -rf ${project_root}/../build/negative-compiler-tests/CMakeLists.txt
touch ${project_root}/../build/negative-compiler-tests/CMakeLists.txt

echo 'cmake_minimum_required(VERSION 3.16)' >> ${project_root}/../build/negative-compiler-tests/CMakeLists.txt
echo 'project(demo LANGUAGES CXX)' >> ${project_root}/../build/negative-compiler-tests/CMakeLists.txt
echo "find_package(GTest REQUIRED)" >> ${project_root}/../build/negative-compiler-tests/CMakeLists.txt
echo 'set(CMAKE_CXX_STANDARD 20)'>> ${project_root}/../build/negative-compiler-tests/CMakeLists.txt
echo 'set(CMAKE_EXPORT_COMPILE_COMMANDS ON)' >> ${project_root}/../build/negative-compiler-tests/CMakeLists.txt
echo 'add_executable(RUN_NEGATIVE_TESTS ${CMAKE_CURRENT_LIST_DIR}/NegativeCompilerTests.cpp)' >> ${project_root}/../build/negative-compiler-tests/CMakeLists.txt

cd ${project_root}/../build/negative-compiler-tests
mkdir ./build
cd ./build
cmake .. 
make >> result.log 2>&1
if grep -F "static_assert" result.log
then
    echo "static_assert"
fi
