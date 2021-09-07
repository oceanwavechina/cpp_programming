project(CPPPTRICKS)
cmake_minimum_required(VERSION 3.6)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -O2 -std=c++98")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Os -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")

if(0)
# fork_test.cpp
set(fork_test_SRC fork_test.cpp)
add_executable(fork_test ${fork_test_SRC})


# class_derive_1.cpp
set(class_derive_1_SRC class_derive_1.cpp)
add_executable(class_derive_1 ${class_derive_1_SRC})

# class_derive_slicing.cpp
set(class_derive_slicing_SRC class_derive_slicing.cpp)
add_executable(class_derive_slicing ${class_derive_slicing_SRC})

# derived_class_exe_order.cpp
set(derived_class_exe_order_SRC derived_class_exe_order.cpp)
add_executable(derived_class_exe_order ${derived_class_exe_order_SRC})

# test_new.cpp
set(test_new_SRC test_new.cpp)
add_executable(test_new ${test_new_SRC})

# varaibles.cpp
set(varaibles_SRC varaibles.cpp)
add_executable(varaibles ${varaibles_SRC})

# size_vs_empty.cpp
set(size_vs_empty_SRC size_vs_empty.cpp)
add_executable(size_vs_empty ${size_vs_empty_SRC})

# toy_coroutine.cpp
set(toy_coroutine_SRC toy_coroutine.cpp)
add_executable(toy_coroutine ${toy_coroutine_SRC})

# Duffs_device.cpp
set(Duffs_device_SRC Duffs_device.cpp)
add_executable(Duffs_device ${Duffs_device_SRC})

# class_derive_same_data_member.cpp
set(class_derive_same_data_member_SRC class_derive_same_data_member.cpp)
add_executable(class_derive_same_data_member ${class_derive_same_data_member_SRC})

# template_tricks.cpp
set(template_tricks_SRC template_tricks.cpp)
add_executable(template_tricks ${template_tricks_SRC})

# comma_expression_tricks.cpp
set(comma_expression_tricks_SRC comma_expression_tricks.cpp)
add_executable(comma_expression_tricks ${comma_expression_tricks_SRC})

# reverse_pair_tricks.cpp
set(reverse_pair_tricks_SRC reverse_pair_tricks.cpp)
add_executable(reverse_pair_tricks ${reverse_pair_tricks_SRC})

# macro_tricks.cpp
set(macro_tricks_SRC macro_tricks.cpp)
add_executable(macro_tricks ${macro_tricks_SRC})

# execute_func_before_main.cpp
set(execute_func_before_main_SRC execute_func_before_main.cpp)
add_executable(execute_func_before_main ${execute_func_before_main_SRC})

# virtual_func_of_null_object.cpp
set(virtual_func_of_null_object_SRC virtual_func_of_null_object.cpp)
add_executable(virtual_func_of_null_object ${virtual_func_of_null_object_SRC})

# number_implicit_convert.cpp
set(number_implicit_convert_SRC number_implicit_convert.cpp)
add_executable(number_implicit_convert ${number_implicit_convert_SRC})

# stack_unwinding_in_exception.cpp
set(stack_unwinding_in_exception_SRC stack_unwinding_in_exception.cpp)
add_executable(stack_unwinding_in_exception ${stack_unwinding_in_exception_SRC})

# access_private_member_data.cpp
set(access_private_member_data_SRC access_private_member_data.cpp)
add_executable(access_private_member_data ${access_private_member_data_SRC})

# forbid_instial_base_class.cpp
set(forbid_instial_base_class_SRC forbid_instial_base_class.cpp)
add_executable(forbid_instial_base_class ${forbid_instial_base_class_SRC})

# noncopyable.cpp
set(noncopyable_SRSC noncopyable.cpp)
add_executable(noncopyable ${noncopyable_SRSC})

# sizeof_impl_and_address_calculate.cpp
set(sizeof_impl_and_address_calculate_SRSC sizeof_impl_and_address_calculate.cpp)
add_executable(sizeof_impl_and_address_calculate ${sizeof_impl_and_address_calculate_SRSC})

# inherit_STL_templete.cpp
set(inherit_STL_templete_SRSC inherit_STL_templete.cpp)
add_executable(inherit_STL_templete ${inherit_STL_templete_SRSC})

# object_initialize_list_order.cpp
set(object_initialize_list_order_SRSC object_initialize_list_order.cpp)
add_executable(object_initialize_list_order ${object_initialize_list_order_SRSC})

# reference_member.cpp
set(reference_member_SRSC reference_member.cpp)
add_executable(reference_member ${reference_member_SRSC})

# test_new.cpp
set(test_new_SRC test_new.cpp)
add_executable(test_new ${test_new_SRC})

# the_const.cpp
set(the_const_SRC the_const.cpp)
add_executable(the_const ${the_const_SRC})

# virtual_func_of_null_object.cpp
set(virtual_func_of_null_object_SRC virtual_func_of_null_object.cpp)
add_executable(virtual_func_of_null_object ${virtual_func_of_null_object_SRC})

# class_derive_same_data_member.cpp
set(class_derive_same_data_member_SRC class_derive_same_data_member.cpp)
add_executable(class_derive_same_data_member ${class_derive_same_data_member_SRC})

endif(0)


# memory_leak_detection.cpp
set(memory_leak_detection_SRC memory_leak_detection.cpp)
add_executable(memory_leak_detection ${memory_leak_detection_SRC})


