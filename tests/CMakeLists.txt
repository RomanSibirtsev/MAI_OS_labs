include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)



set(CMAKE_CXX_FLAGS "-lzmq")
add_compile_options(-Wno-error=deprecated-declarations -Wdeprecated-declarations)

add_executable(lab5-7_test lab5-7_test.cpp ../lab5-7/src/node.cpp ../lab5-7/src/socket.cpp)
target_link_libraries(lab5-7_test PRIVATE GTest::GTest)
target_include_directories(lab5-7_test PRIVATE ../lab5-7/include)

target_link_libraries(lab5-7_test PRIVATE zmq)

add_test(lab5-7_test lab5-7_test)