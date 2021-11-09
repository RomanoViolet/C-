#!/usr/bin/env bash
project_root=$(pwd)
echo "project_root: ${project_root}"
if [[ -d "${project_root}/../build/negative-compiler-tests-CPP20" ]]
then
    rm -rf ${project_root}/../build/negative-compiler-tests-CPP20
fi

mkdir ${project_root}/../build/negative-compiler-tests-CPP20
cp -r ./NegativeCompilerTests_CPP20Concepts.cpp ./*.hpp ./*.inl ${project_root}/../build/negative-compiler-tests-CPP20/
rm -rf ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt
touch ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt

echo 'cmake_minimum_required(VERSION 3.16)' >> ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt
echo 'project(demo LANGUAGES CXX)' >> ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt
echo "find_package(GTest REQUIRED)" >> ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt
echo 'set(CMAKE_CXX_STANDARD 20)'>> ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt
echo 'set(CMAKE_EXPORT_COMPILE_COMMANDS ON)' >> ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt
echo 'add_executable(RUN_NEGATIVE_TESTS ${CMAKE_CURRENT_LIST_DIR}/NegativeCompilerTests_CPP20Concepts.cpp)' >> ${project_root}/../build/negative-compiler-tests-CPP20/CMakeLists.txt

cd ${project_root}/../build/negative-compiler-tests-CPP20
mkdir ./build
cd ./build
cmake .. 
make >> result.log 2>&1

if grep -F "error: template constraint failure" result.log
then
    echo "constraint_error"
fi

if grep -F "error: constraints not satisfied" result.log
then
    echo "constraint_error"
fi
