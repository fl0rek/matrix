#include <iostream>
#include <string>
#include <assert.h>

#include "FDeque.hpp"
#include "Matrix.hpp"


void test_matrix();
void test_fdeque();

int main() {
	std::cout << "Hello, World!" << std::endl;

	std::string foo;

	test_matrix();
	test_fdeque();

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

void test_matrix_denominator() {
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

void test_matrix() {
	test_matrix_construct_and_equality();
	test_matrix_denominator();
	test_matrix_inequality();
	test_matrix_multiplication();
	test_matrix_multiplication2();
	test_matrix_sum();
	test_matrix_sub();

	std::cout << "test Matrix<T> passed!" << std::endl;
}

Matrix<double> m0{0};
Matrix<double> m1{1};
Matrix<double> m2{2};
Matrix<double> m3{3};
Matrix<double> m4{4};

void test_fdeque_construction_and_comparator() {
	FDeque<Matrix<double>> a{};
	a.push_back(m0).push_back(m1).push_back(m2);
	FDeque<Matrix<double>> b{a};
	assert(a == b);
}

void test_fdeque_intersections() {
	FDeque<Matrix<double>> a{};
	a.push_back(m0).push_back(m3).push_back(m4);
	FDeque<Matrix<double>> b{};
	b.push_back(m1).push_back(m3).push_back(m4);

	FDeque<Matrix<double>> c{};
	c.push_back(m3).push_back(m4);
	std::cout << a << "\nb\n" << b << "\nc\n" << c << std::endl;
	assert(a*b == c);
}

void test_fdeque_push_pop() {
	FDeque<Matrix<double>> a{};
	a.push_front(m0).push_back(m1);
	assert(a.pop_front() == m0);
	assert(a.pop_front() == m1);
}

void test_fdeque() {
	test_fdeque_construction_and_comparator();
	test_fdeque_intersections();
	//test_fdeque_push_pop();
	std::cout << "test FDeque<T> passed!" << std::endl;
}
