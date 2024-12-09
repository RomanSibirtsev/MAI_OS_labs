set(CMAKE_C_STANDARD 17)

add_executable(lab3 include/utils.hpp
        main.cpp
        src/parent.cpp
        src/utils.cpp)


target_include_directories(lab3 PRIVATE include)

add_executable(lower.out
        src/lower.cpp
        ./src/utils.cpp
        ./include/utils.hpp)

target_include_directories(lower.out PRIVATE include)

add_executable(underscore.out
        src/underscore.cpp
        ./src/utils.cpp
        ./include/utils.hpp)

target_include_directories(underscore.out PRIVATE include)

find_package(Threads REQUIRED)
target_link_libraries(lower.out PRIVATE pthread)
target_link_libraries(lower.out PRIVATE rt)

target_link_libraries(underscore.out PRIVATE pthread)
target_link_libraries(underscore.out PRIVATE rt)

target_link_libraries(lab3 PRIVATE pthread)
target_link_libraries(lab3 PRIVATE rt)

add_dependencies(lab3 underscore.out lower.out)