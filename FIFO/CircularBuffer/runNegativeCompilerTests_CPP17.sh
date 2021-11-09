#!/usr/bin/env bash
project_root=$(pwd)
echo "project_root: ${project_root}"
if [[ -d "${project_root}/../build/negative-compiler-tests-CPP17" ]]
then
    rm -rf ${project_root}/../build/negative-compiler-tests-CPP17
fi

mkdir ${project_root}/../build/negative-compiler-tests-CPP17
cp -r ./NegativeCompilerTests_CPP17.cpp ./*.hpp ./*.inl ${project_root}/../build/negative-compiler-tests-CPP17/
rm -rf ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt
touch ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt

echo 'cmake_minimum_required(VERSION 3.16)' >> ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt
echo 'project(demo LANGUAGES CXX)' >> ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt
echo "find_package(GTest REQUIRED)" >> ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt
echo 'set(CMAKE_CXX_STANDARD 20)'>> ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt
echo 'set(CMAKE_EXPORT_COMPILE_COMMANDS ON)' >> ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt
echo 'add_executable(RUN_NEGATIVE_TESTS ${CMAKE_CURRENT_LIST_DIR}/NegativeCompilerTests_CPP17.cpp)' >> ${project_root}/../build/negative-compiler-tests-CPP17/CMakeLists.txt

cd ${project_root}/../build/negative-compiler-tests-CPP17
mkdir ./build
cd ./build
cmake .. 
make >> result.log 2>&1

if grep -F "initializer but incomplete type" result.log
then
    echo "incomplete type"
fi
