cmake_minimum_required(VERSION 3.27)

project(
        Abelian-Sandpile-Model
        VERSION 1.0
        DESCRIPTION "Abelian Sandpile Model as BMP File"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(bin)
add_subdirectory(lib)