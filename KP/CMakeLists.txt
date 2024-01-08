set(CMAKE_C_STANDARD 17)

add_executable(kp
        main.cpp
        ./src/MCKAllocator.cpp
        ./include/MCKAllocator.hpp
        ./src/FBLAllocator.cpp
        ./include/FBLAllocator.hpp)

target_include_directories(kp PRIVATE include)