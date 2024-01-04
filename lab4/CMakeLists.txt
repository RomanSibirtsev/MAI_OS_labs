cmake_minimum_required(VERSION 3.20)
project(lab4)

add_library(lib1 SHARED src/lib1.cpp)
add_library(lib2 SHARED src/lib2.cpp)

target_include_directories(lib1 PUBLIC include)
target_include_directories(lib2 PUBLIC include)

add_executable(main_static main_static.cpp)
add_executable(main_dynamic main_dynamic.cpp)

target_link_libraries(main_static PRIVATE lib1)

target_include_directories(main_dynamic PRIVATE include)