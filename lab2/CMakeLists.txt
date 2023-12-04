set(CMAKE_C_STANDARD 17)

add_executable(lab2
        main.cpp
        ./src/timsort.cpp
        ./include/timsort.hpp)

target_include_directories(lab2 PRIVATE include)