#pragma once 

#include<cstdint>
#include<iostream>

/*
 * == autor: Miko?aj Florkiewicz
 * == grupa: 2I3
 * == zadanie: macierze 
 * == projekt: 1605
 */

class Matrix;

class Matrix {
	public:
		Matrix(int64_t, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t, int64_t);
		Matrix(int64_t);
		Matrix();
/*
		Matrix(Matrix &&);
		Matrix(const Matrix &);
		Matrix& operator=(const Matrix);
*/
		~Matrix();

		Matrix& operator+=(const Matrix &);
		Matrix& operator-=(const Matrix &);
		Matrix& operator*=(const Matrix &);

		const Matrix operator+(const Matrix &) const ;
		const Matrix operator-(const Matrix &) const ;
		const Matrix operator*(const Matrix &) const;

		bool operator==(const Matrix &) const;
		bool operator!=(const Matrix &) const;

		int64_t denominator() const;

		friend std::ostream& operator<<(std::ostream &, const Matrix &);

	private:
		/**
		 * swap two matrix objects
		 */
		static void swap(Matrix & lhs, Matrix & rhs);
		/**
		 * total number of elements in matrix 
		 */
		static constexpr uint32_t matrix_size = 9;
		/**
		 * successive matrix elements 
		 * in columnwise order from left top
		 */
		int64_t vals[matrix_size];
	       	
};
