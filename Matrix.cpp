#include "matrix.hh"
#include <algorithm>
#include <iostream>

/**
 * debug macro
 */
#ifdef _DEBUG
#define D(x) x
#else
#define D(x)
#endif

/**
 * main constructor,
 * builds matrix columnwise from top left
 */
Matrix::Matrix(int64_t v0, int64_t v1, int64_t v2, int64_t v3, int64_t v4, int64_t v5, int64_t v6,
			   int64_t v7, int64_t v8) {
	D(std::cout << "Wywołano konstruktor Matrix(9 int64_t) : " << "\n" <<
	  v0 << " " <<
	  v1 << " " <<
	  v2 << " " <<
	  v3 << " " <<
	  v4 << " " <<
	  v5 << " " <<
	  v6 << " " <<
	  v7 << " " <<
	  v8 << " "
	  << "[" << __FILE__ << ":" << __LINE__ << "]" << std::endl;)
	this->vals[0] = v0;
	this->vals[1] = v1;
	this->vals[2] = v2;
	this->vals[3] = v3;
	this->vals[4] = v4;
	this->vals[5] = v5;
	this->vals[6] = v6;
	this->vals[7] = v7;
	this->vals[8] = v8;
}

/**
 * returns unit matrix multiplied by v
 */
Matrix::Matrix(int64_t v)
		: Matrix::Matrix(v, 0, 0, 0, v, 0, 0, 0, v) {
	D(std::cout << "Wywołano konstruktor Matrix(1 int64_t) : " << v
	  << "[" << __FILE__ << ":" << __LINE__ << "]" << std::endl;)
}

/**
 * default is unit Matrix
 */
Matrix::Matrix()
		: Matrix::Matrix(1) {
	D(std::cout << "Wywołano konstruktor Matrix() : "
	  << "[" << __FILE__ << ":" << __LINE__ << "]" << std::endl;)
}

Matrix::~Matrix() {
	D(std::cout << "Wywołano destruktor"
	  << "[" << __FILE__ << ":" << __LINE__ << "]" << std::endl;)
}
/*
Matrix::Matrix(Matrix && rhs) 
	: Matrix(0) {
	std::cout << "Wywołano konstruktor Matrix(Matrix&&) : " << std::endl;
	swap(*this, rhs);
}

Matrix::Matrix(const Matrix & rhs) 
	: Matrix(0) {
	std::cout << "Wywołano konstruktor Matrix(Matrix&) : " << std::endl;
	for(uint32_t i = 0; i < this->matrix_size; i++)
		this->vals[i] = rhs.vals[i];
}
Matrix& Matrix::operator=(Matrix rhs) {
	swap(*this, rhs);
	return *this;
}
*/

/**
 * dumb swapping of arrays 
 * strong exception guarantee
 */
void Matrix::swap(Matrix & lhs, Matrix & rhs) {
	using std::swap;
	swap(lhs.vals, rhs.vals);
}

Matrix &Matrix::operator+=(const Matrix &rhs) {
	for (uint32_t i = 0; i < this->matrix_size; ++i) {
		this->vals[i] += rhs.vals[i];
	}
	return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs) {
	for (uint32_t i = 0; i < this->matrix_size; ++i) {
		this->vals[i] -= rhs.vals[i];
	}
	return *this;
}

/**
 * matrix multiplication,
 * creates temporary object and fills it with values, then swaps self with it
 * O(n^3) complexity 
 */
Matrix &Matrix::operator*=(const Matrix &rhs) {
	uint32_t row_len = sqrt(this->matrix_size);

	Matrix tmp(0);

	for (uint32_t row = 0; row < row_len; row++) {
		for (uint32_t col = 0; col < row_len; col++) {
			for (uint32_t k = 0; k < row_len; k++) {
				tmp.vals[row * row_len + col] +=
						this->vals[row * row_len + k] * rhs.vals[col * row_len + k];
			}
		}
	}
	swap(*this, tmp);
	return *this;
}

/**
 * defined in terms of += operator
 */
const Matrix Matrix::operator+(const Matrix &rhs) const {
	return Matrix(*this) += rhs;
}

/**
 * defined in terms of += operator
 */
const Matrix Matrix::operator-(const Matrix &rhs) const {
	return Matrix(*this) -= rhs;

}

/**
 * defined in terms of += operator
 */
const Matrix Matrix::operator*(const Matrix &rhs) const {
	return Matrix(*this) *= rhs;

}

/**
 * equality by values
 */
bool Matrix::operator==(const Matrix &rhs) const {
	for (uint32_t i = 0; i < this->matrix_size; ++i) {
		if (this->vals[i] != rhs.vals[i])
			return false;
	}
	return true;
}

/**
 * defined in terms of == operator (follows law of excluded middle)
 */
bool Matrix::operator!=(const Matrix &rhs) const {
	return !*this == rhs;
}

/**
 * calculates denominator using standard algorythm for 3x3 matrices
 */
int64_t Matrix::denominator() const {
	uint32_t row_len = sqrt(this->matrix_size);
	int64_t plus = 0;
	int64_t minus = 0;
	for (uint32_t i = 0; i < row_len; i++) {
		int64_t plus_delta = 1;
		int64_t minus_delta = 1;
		for (uint32_t j = 0; j < row_len; j++) {
			plus_delta *= this->vals[(i + ((row_len + 1) * j)) % this->matrix_size];
			minus_delta *= this->vals[(i - ((row_len + 1) * j)) % this->matrix_size];
		}
		plus += plus_delta;
		minus += minus_delta;
	}
	return plus - minus;
}

/**
 * attempts to print matrix in some sane way, using tab as delimiter
 * (may not look as good for matrix having both small and big elements)
 */
std::ostream &operator<<(std::ostream &o, const Matrix &m) {
	uint32_t row_len = sqrt(m.matrix_size);
	for (uint32_t i = 0; i < m.matrix_size; ++i) {
		o << m.vals[i] << "\t";
		if (!((i + 1) % row_len))
			o << "\n";
	}
	return o << std::flush;
}

#undef D
/*
 * == autor: Mikolaj Florkiewicz
 * == grupa: 2I3
 * == zadanie: macierze 
 * == projekt: 1605
 */
