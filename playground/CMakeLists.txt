project(Playground)
cmake_minimum_required(VERSION 3.6)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -O2 -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -g")

include_directories(
    /usr/local/opt/openssl/include
)


link_directories(
    "/usr/local/opt/openssl/lib"
)




# test_dummy
set(test_dummy_SRC test_dummy.cpp)
add_executable(test_dummy ${test_dummy_SRC})
target_link_libraries(test_dummy jsoncpp boost_system)

if(0)
# aws4_signature
set(aws4_signature_SRC aws4_signature.cpp)
add_executable(aws4_signature ${aws4_signature_SRC})
target_link_libraries(aws4_signature ssl crypto curl)





# test system call wrapper
set(systemcall_test_SRC systemcall_test.cpp)
add_executable(systemcall_test ${systemcall_test_SRC})

endif(0)
