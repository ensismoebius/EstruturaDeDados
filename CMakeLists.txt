cmake_minimum_required(VERSION 3.5)

project(EstruturaDeDados LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EstruturaDeDados
    lib/linkedList.cpp
    lib/binaryTree.cpp
    lib/stack.cpp
    lib/ktree.cpp
    lib/heap.cpp
    lib/strFuncs.cpp
    lib/calculator.cpp
    main.cpp)

install(TARGETS EstruturaDeDados
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
