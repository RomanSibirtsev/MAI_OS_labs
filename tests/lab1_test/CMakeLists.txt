set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_test lab1_test.cpp
                ../../lab1/src/parent.cpp
                ../../lab1/include/parent.hpp)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../../lab1/include)

add_test(lab1_test lab1_test)