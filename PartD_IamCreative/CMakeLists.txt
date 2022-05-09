cmake_minimum_required(VERSION 3.21)
project(CSC340Asmt04)

set(CMAKE_CXX_STANDARD 20)

add_executable(run_d BagInterface.h Include.h LinkedBag.cpp LinkedBag.h LinkedBag340.cpp Node.cpp Node.h PartD.cpp)