set(CMAKE_CXX_STANDARD 17)

add_executable(lab1_test lab1_test.cpp
                ../../lab1/src/parent.cpp
                ../../lab1/include/parent.hpp)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../../lab1/include)

configure_file(test1_res.txt test1_res.txt)
configure_file(test1_src.txt test1_src.txt)

configure_file(test2_res.txt test2_res.txt)
configure_file(test2_src.txt test2_src.txt)

configure_file(test3_res.txt test3_res.txt)
configure_file(test3_src.txt test3_src.txt)

add_dependencies(lab1_test underscore.out lower.out)

add_test(lab1_test lab1_test)