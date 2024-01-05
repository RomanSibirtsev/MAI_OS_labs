set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-lzmq")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_compile_options(-Wno-error=deprecated-declarations -Wdeprecated-declarations)

add_executable(control include/node.hpp include/socket.hpp
        src/node.cpp src/socket.cpp src/control.cpp
)
target_include_directories(control PRIVATE include)

add_executable(calculate include/node.hpp include/socket.hpp
        src/node.cpp src/socket.cpp src/calculate.cpp
)
target_include_directories(calculate PRIVATE include)

target_link_libraries(control PRIVATE zmq)

target_link_libraries(calculate PRIVATE zmq)