#include <iostream>
#include <string>
#include <assert.h>

#include "FDeque.hpp"
#include "Matrix.hpp"


void test_matrix();

int main() {
	std::cout << "Hello, World!" << std::endl;

	std::string foo;

	test_matrix();

	std::cout << "Tests Passed!" <<std::endl;
	std::getline(std::cin, foo);
	return 0;
}

void test_matrix_construct_and_equality() {
	Matrix<double> a{};
	Matrix<double> b{1, 0, 0, 0, 1, 0, 0, 0, 1};
	assert(a == a);
	assert(a == b);
}

void test_matrix_inequality() {
	Matrix<double> a{};
	assert(!(a != a));
}

void test_matrix_denomintaor() {
	Matrix<double> a{};
	assert(fabs(a.denominator() - 1) < std::numeric_limits<double>::epsilon());
}

void test_matrix_multiplication() {
	Matrix<double> a{};
	Matrix<double> b{2};
	assert(a*b == b);
}

void test_matrix_multiplication2() {
	Matrix<double> a{2};
	Matrix<double> b{1,2,3,4,5,6,7,8,9};
	Matrix<double> c{2,4,6,8,10,12,14,16,18};
	assert(a*b == c);
	a *= b;
	assert(a == c);
}

void test_matrix_sum() {
	Matrix<double> a{};
	Matrix<double> b{1,1,1,1,1,1,1,1,1};
	Matrix<double> c{2,1,1,1,2,1,1,1,2};
	assert(a+b == c);
	a += b;
	assert(a == c);
}

void test_matrix_sub() {
	Matrix<double> a{};
	Matrix<double> b{2,1,1,1,2,1,1,1,2};
	Matrix<double> c{1,1,1,1,1,1,1,1,1};
	assert(b-a == c);
	b -= a;
	assert(b == c);
}

void test_matrix(){
	test_matrix_construct_and_equality();
	test_matrix_denomintaor();
	test_matrix_inequality();
	test_matrix_multiplication();
	test_matrix_multiplication2();
	test_matrix_sum();
	test_matrix_sub();

	std::cout << "test Matrix<T> passed!" << std::endl;
}
