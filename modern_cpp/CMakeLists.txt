project(modern_cpp)
cmake_minimum_required(VERSION 3.6)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -O2 -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11 -g")

include_directories(
    /usr/local/opt/openssl/include
)

link_directories(
    "/usr/local/opt/openssl/lib"
)

if(0)

# 1_initialization
set(1_initialization_SRC 1_initialization.cpp)
add_executable(1_initialization ${1_initialization_SRC})
target_link_libraries(1_initialization)

# 2_auto_type
set(2_auto_type_SRC 2_auto_type.cpp)
add_executable(2_auto_type ${2_auto_type_SRC})

# 3_for_each
set(3_for_each_SRC 3_for_each.cpp)
add_executable(3_for_each ${3_for_each_SRC})

# 4_nullptr
set(4_nullptr_SRC 4_nullptr.cpp)
add_executable(4_nullptr ${4_nullptr_SRC})

# 5_enum_class
set(5_enum_class_SRC 5_enum_class.cpp)
add_executable(5_enum_class ${5_enum_class_SRC})

# 6_static_assert
set(6_static_assert_SRC 6_static_assert.cpp)
add_executable(6_static_assert ${6_static_assert_SRC})

# 7_delegating_constructor
set(7_delegating_constructor_SRC 7_delegating_constructor.cpp)
add_executable(7_delegating_constructor ${7_delegating_constructor_SRC})

# 8_virutual_function_override
set(8_virutual_function_override_SRC 8_virutual_function_override.cpp)
add_executable(8_virutual_function_override ${8_virutual_function_override_SRC})

# 9_final_delete
set(9_final_delete_SRC 9_final_delete.cpp)
add_executable(9_final_delete ${9_final_delete_SRC})

# 10_constexpr
set(10_constexpr_SRC 10_constexpr.cpp)
add_executable(10_constexpr ${10_constexpr_SRC})

# 11_lambda_function
set(11_lambda_function_SRC 11_lambda_function.cpp)
add_executable(11_lambda_function ${11_lambda_function_SRC})

# 12_multi_threading_basic
set(12_multi_threading_basic_SRC 12_multi_threading_basic.cpp)
add_executable(12_multi_threading_basic ${12_multi_threading_basic_SRC})

endif(0)


# 13_multi_threading_lock_lazy_init
set(13_multi_threading_lock_lazy_init_SRC 13_multi_threading_lock_lazy_init.cpp)
add_executable(13_multi_threading_lock_lazy_init ${13_multi_threading_lock_lazy_init_SRC})

