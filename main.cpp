#include <iostream>

#include "FDeque.hpp"
using namespace std;
int main() {
	cout << "Hello, World!" << endl;

	//FDeque<int> a{};
	auto a = FDeque<std::string>{};
	//a.push_back(std::string("foo"));
	for(auto it : a) {
		std::cout << a;
	}
	return 0;
}