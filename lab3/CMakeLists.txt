set(CMAKE_C_STANDARD 17)

add_executable(lab3
        main.cpp
        ./src/parent.cpp
        ./include/parent.hpp)

target_include_directories(lab3 PRIVATE include)

add_executable(lower.out
        src/lower.cpp)


add_executable(underscore.out
        src/underscore.cpp)

add_dependencies(lab3 underscore.out lower.out)