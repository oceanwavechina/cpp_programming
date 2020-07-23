project(zookeeper_box)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++2a -g")

include_directories(
    /usr/local/include
)

link_directories(
    "/usr/local/lib"
)

# test
set(test_SRC test.cpp)
add_executable(test ${test_SRC})
target_link_libraries(test zookeeper_mt)