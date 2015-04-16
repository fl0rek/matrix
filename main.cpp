#include <iostream>
#include <string>

#include "FDeque.hpp"

using namespace std;

int main() {
	cout << "Hello, World!" << endl;

	//FDeque<int> a{};
	auto a = FDeque<string>{};
	//a.push_back(std::string("foo"));
	return 0;
}
