#include <iostream>
#include <string>

#include "FDeque.hpp"
#include "Matrix.hpp"

using namespace std;

int main() {
	cout << "Hello, World!" << endl;

	//FDeque<int> a{};
	auto a = FDeque<double>{};
	auto b = FDeque<double>{};
	a.push_back(2);
	std::string foo;
	std::getline(std::cin, foo);
	for(auto it = a.begin(); it != a.end(); it++)
		std::cout << *it;
	return 0;
}
