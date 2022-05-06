cmake_minimum_required(VERSION 3.21)
project(CSC340Asmt04)

set(CMAKE_CXX_STANDARD 20)

add_executable(PartA_LinkedBag340
        BagInterface.h Include.h LinkedBag.cpp LinkedBag.h LinkedBag340.cpp LinkedBagClient340.cpp Node.cpp Node.h)