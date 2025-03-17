/*
 * inline_namespace.cpp
 *
 *  Created on: Mar 16, 2025
 *      Author: liuyanan
 */

#include <iostream>

// 内联命名空间， 对于版本的升级比较友好
namespace parent {

    namespace v1 {

        void foo() {std::cout << "v1::foo()" << std::endl;}

    }  // namespace child1


    inline namespace v2 {

        void foo() {std::cout << "v2::foo()" << std::endl;}

    }  // namespace child_inline


}  // namespace name


// 嵌套命名空间

namespace a::b::c {
    void foo() {std::cout << "a::b::c::foo()" << std::endl;}
}


int main(int argc, char **argv) {

    parent::v1::foo();

    parent::v2::foo();

    parent::foo();

    a::b::c::foo();
}


// g++ --std=c++2a inline_namespace.cpp
