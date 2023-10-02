set(CMAKE_C_STANDARD 17)

add_executable(lab1
        main.cpp)

target_include_directories(lab1 PRIVATE include)

add_executable(lower.out
        src/lower.cpp)


add_executable(underscore.out
        src/underscore.cpp)

add_dependencies(lab1 underscore.out lower.out)