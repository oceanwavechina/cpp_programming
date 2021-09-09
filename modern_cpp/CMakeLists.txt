project(modern_cpp)
cmake_minimum_required(VERSION 3.6)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -O2 -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++2a -g")

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

# weak_ptr_and_cycle_ref
set(weak_ptr_and_cycle_ref_SRC weak_ptr_and_cycle_ref.cpp)
add_executable(weak_ptr_and_cycle_ref ${weak_ptr_and_cycle_ref_SRC})

# rvalue_lvalue_forward
set(rvalue_lvalue_forward_SRC rvalue_lvalue_forward.cpp)
add_executable(rvalue_lvalue_forward ${rvalue_lvalue_forward_SRC})

# memory_order
set(memory_order_SRC memory_order.cpp)
add_executable(memory_order ${memory_order_SRC})

# 5_enum_class
set(5_enum_class_SRC 5_enum_class.cpp)
add_executable(5_enum_class ${5_enum_class_SRC})

# move
set(move_SRC move.cpp)
add_executable(move ${move_SRC})

# 7_delegating_constructor
set(7_delegating_constructor_SRC 7_delegating_constructor.cpp)
add_executable(7_delegating_constructor ${7_delegating_constructor_SRC})

# override_identifier
set(override_identifier_SRC override_identifier.cpp)
add_executable(override_identifier ${override_identifier_SRC})

# final_delete
set(final_delete_SRC final_delete.cpp)
add_executable(final_delete ${final_delete_SRC})

# 10_constexpr
set(10_constexpr_SRC 10_constexpr.cpp)
add_executable(10_constexpr ${10_constexpr_SRC})

# 11_lambda_function
set(11_lambda_function_SRC 11_lambda_function.cpp)
add_executable(11_lambda_function ${11_lambda_function_SRC})

# 12_multi_threading_basic
set(12_multi_threading_basic_SRC 12_multi_threading_basic.cpp)
add_executable(12_multi_threading_basic ${12_multi_threading_basic_SRC})

# 13_multi_threading_lock_lazy_init
set(13_multi_threading_lock_lazy_init_SRC 13_multi_threading_lock_lazy_init.cpp)
add_executable(13_multi_threading_lock_lazy_init ${13_multi_threading_lock_lazy_init_SRC})

# enable_shared_from_this
set(enable_shared_from_this_SRC 14_pointers.cpp)
add_executable(enable_shared_from_this ${enable_shared_from_this_SRC})

# macro_var_arg
set(macro_var_arg_SRC macro_var_arg.cpp)
add_executable(macro_var_arg ${macro_var_arg_SRC})

# shared_ptr 
set(shared_ptr_SRC shared_ptr.cpp)
add_executable(shared_ptr ${shared_ptr_SRC})

# weak_ptr_and_cycle_ref
set(weak_ptr_and_cycle_ref_SRC weak_ptr_and_cycle_ref.cpp)
add_executable(weak_ptr_and_cycle_ref ${weak_ptr_and_cycle_ref_SRC})

# memory_order
set(memory_order_SRC memory_order.cpp)
add_executable(memory_order ${memory_order_SRC})

endif(0)

# var_arg_template
set(var_arg_template_SRC var_arg_template.cpp)
add_executable(var_arg_template ${var_arg_template_SRC})

