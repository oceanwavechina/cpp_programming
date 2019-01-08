project(IceClientTest)
cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -g")

include_directories(
    .
)


# test_dummy
set(client_test_SRC client_test.cpp Hello.cpp IceClient.cpp)
add_executable(client_test ${client_test_SRC})
target_link_libraries(client_test Ice IceUtil IceGrid Glacier2)
