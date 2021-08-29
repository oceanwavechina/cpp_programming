#include <iostream>
#include <vector>
#include <thread>

using namespace std;

/*
  	  TODO:
  	  	   如何复现问题？？
 */

class TheMemoryOrderProblem {
public:
	TheMemoryOrderProblem() :a(0), b(0) { }

	void runner_1() {
		a = 1;
		b = 2;
	}

	void runner_2() {
		if(b == 2) {
			//assert(a == 1);
			if(a != 1) {
				throw runtime_error("got memory order problem");
			}
			//cout << "a=" << a << endl;
		}
	}

	void show() {
		std::thread t2(&TheMemoryOrderProblem::runner_2, this);
		std::thread t1(&TheMemoryOrderProblem::runner_1, this);

		t1.join();
		t2.join();
	}

private:
	int a;
	int b;
};

void run_the_memory_order_problem()
{
	while(1) {
		try{
			TheMemoryOrderProblem problem;
			problem.show();
		} catch (const std::exception& e) {
			cout << "exception: " << e.what() << endl;
			break;
		}
	}
}


int main(int argc, char const *argv[])
{

	run_the_memory_order_problem();

	system("sleep 30");

    return 0;
}
