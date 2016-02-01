#include <iostream>

class enemy {
	enemy() = default;
};

struct test {
	enemy* e1;
};

int main() {
	using std::cout;
	using std::endl;

	cout << "This is Yulong" << endl;
	cout << "Testing Testing" << endl;

	return 0;
}