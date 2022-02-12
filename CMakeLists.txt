cmake_minimum_required(VERSION 3.5 )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project( Huffman )

include_directories( include )

add_executable( test_main apps/main.cpp )
