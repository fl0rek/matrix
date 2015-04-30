#pragma once 

#include<cstdint>
#include<iostream>

/*
 * == autor: Miko³aj Florkiewicz
 * == grupa: 2I3
 * == zadanie: macierze 
 * == projekt: 1605
 */


template<typename T>
class Matrix {
public:
	Matrix(T v0, T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8) {
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

	Matrix(T v)
			: Matrix::Matrix(v, zero_value, zero_value, zero_value, v, zero_value, zero_value,
							 zero_value, v) {
	}

	Matrix()
			: Matrix::Matrix(one_value) { }

/*
		Matrix(Matrix &&);
		Matrix(const Matrix &);
		Matrix& operator=(const Matrix);
*/
	~Matrix() {};

	Matrix<T> &operator+=(const Matrix<T> &rhs) {
		for (uint32_t i = 0; i < this->matrix_size; ++i) {
			this->vals[i] += rhs.vals[i];
		}
		return *this;
	}

	Matrix<T> &operator-=(const Matrix<T> &rhs) {
		for (uint32_t i = 0; i < this->matrix_size; ++i) {
			this->vals[i] -= rhs.vals[i];
		}
		return *this;
	}

	Matrix<T> &operator*=(const Matrix<T> &rhs) {
		uint32_t row_len = sqrt(this->matrix_size);

		Matrix<T> tmp(zero_value);

		for (uint32_t row = 0; row < row_len; row++) {
			for (uint32_t col = 0; col < row_len; col++) {
				for (uint32_t k = 0; k < row_len; k++) {
					tmp.vals[col * row_len + row] +=
							this->vals[row * row_len + k] * rhs.vals[col * row_len + k];
				}
			}
		}
		swap(*this, tmp);
		return *this;
	}

	const Matrix<T> operator+(const Matrix<T> &rhs) const {
		return Matrix<T>(*this) += rhs;
	}

	const Matrix<T> operator-(const Matrix<T> &rhs) const {
		return Matrix<T>(*this) -= rhs;
	}

	const Matrix<T> operator*(const Matrix<T> &rhs) const {
		return Matrix<T>(*this) *= rhs;
	}

	bool operator==(const Matrix<T> &rhs) const {
		for (uint32_t i = 0; i < this->matrix_size; i++)
			if (this->vals[i] != rhs.vals[i])
				return false;
		return true;
	}

	bool operator!=(const Matrix<T> &rhs) const {
		return !(*this == rhs);
	}

	T denominator() const {
		uint32_t row_len = sqrt(this->matrix_size);
		T plus = zero_value;
		T minus = zero_value;
		for (uint32_t i = 0; i < row_len; i++) {
			int64_t plus_delta = one_value;
			int64_t minus_delta = one_value;
			for (uint32_t j = 0; j < row_len; j++) {
				plus_delta *= this->vals[(i + ((row_len + 1) * j)) % this->matrix_size];
				minus_delta *= this->vals[(i - ((row_len + 1) * j)) % this->matrix_size];
			}
			plus += plus_delta;
			minus += minus_delta;
		}
		return plus - minus;
	}

	friend std::ostream &operator<<(std::ostream &o, const Matrix<T> &m) {
		uint32_t row_len = sqrt(m.matrix_size);
		for (uint32_t i = 0; i < m.matrix_size; ++i) {
			o << m.vals[i] << "\t";
			if (!((i + 1) % row_len))
				o << "\n";
		}
		return o << std::flush;
	}

private:
	/**
	 * swap two matrix objects
	 */
	static void swap(Matrix<T> &lhs, Matrix<T> &rhs) {
		using std::swap;
		swap(lhs.vals, rhs.vals);
	}

	/**
	 * total number of elements in matrix
	 */
	static constexpr uint32_t matrix_size = 9;
	/**
	 * successive matrix elements
	 * in columnwise order from left top
	 */
	T vals[matrix_size];


	static constexpr T zero_value{0};

	static constexpr T one_value{1};
};
