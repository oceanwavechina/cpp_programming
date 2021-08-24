/*
 * empty_function.cpp
 *
 *  Created on: Aug 24, 2021
 *      Author: liuyanan
 */


int num = 0;

const int* get_num_addr()
{
	return &num;
}

const int get_num_val()
{
	return num;
}


/*
// 编译不过，因为 const 只能修饰 member function
int modify_num_val(int& a) const
{
	a += 1;
	return num;
}
*/


class A {
public:
	/*
	// 在编译层面报错
	int read_member_val() const
	{
		x += 1;
		return x;
	}
	*/

	int read_static_val() const
	{
		// 对 static 类型的修改是可以的
		y += 1;
		return y;
	}

private:
	int x;

	static int y;
};

int A::y;



int main(int argc, char **argv) {

	// const 类型的返回一定要用 const 变量接收
	// int* p_a = get_num_addr();
	// int a = get_num_addr();

	// modify_num_val(num);

	A a;
	// a.read_val();
	a.read_static_val();

	return 0;
}
