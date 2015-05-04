#pragma once

#include "commons.h"

#include <typeinfo>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>
#include <iterator>
#include <utility>

template<typename T>
class FDeque {
public:
	typedef T value_type;
	typedef T reference;
	typedef T const_reference;

	/**
	 * so we can use for( : ) syntax
	 */
	const T* begin() const {
		return this->data;
	}

	const T* end() const {
		return this->dataEnd;
	}

	bool contains(T const &el) const {
		for (auto it = this->data; it != this->dataEnd; it++) {
			if (*it == el) {
				return true;
			}
		}
		return false;
	}

	/**
	 * Resizes deque to newSize or throws if unable
	 * Used mostly internally, but there is no harm in exposing it outside
	 */
	FDeque<T> &resize(int newSize) {
		unsigned long offset = this->dataEnd - this->data;
		if (newSize <= offset || newSize < 1)
			throw std::invalid_argument("new size too small");
		T* newdata = new T[newSize];
		uint32_t i = 0;
		for(auto it = this->data; it != this->dataEnd; it++) {
			newdata[i++] = *it;
		}
		delete[] this->data;
		this->data = newdata;
		this->dataEnd = this->data + offset;
		this->currentCapacity = newSize;
		return *this;
	}

	/**
	 * resizes if nessesary
	 */
	FDeque<T> &push_back(const T rhs) {
		if (this->length() - 1 >= this->currentCapacity) {
			this->resize(this->currentCapacity * 2);
		}
		*(this->dataEnd++) = rhs;
		return *this;
	}

	/**
	 * rotates internal array and inserts at 1st position
	 */
	FDeque<T> &push_front(const T &rhs) {
		if (this->length() - 1 >= this->currentCapacity) {
			this->resize(this->currentCapacity * 2);
		}
		std::rotate(this->data, this->dataEnd, this->dataEnd+1);
		*(this->data) = rhs;
		this->dataEnd++;
		return *this;
	}

	/**
	 * frees memory if possible
	 */
	T &pop_back() {
		if (2*this->length() + 10 < this->currentCapacity) {
			this->resize(this->currentCapacity/2);
		}
		return *(--this->dataEnd);
	}

	/**
	 * rotates internal arrayy and pops back
	 */
	T &pop_front() {
		std::rotate(this->data, this->data+1, this->dataEnd);
		return this->pop_back();
	}

	FDeque<T> &operator+=(const FDeque<T> &rhs) {
		for (auto it : rhs) {
			if(!this->contains(it))
				this->push_back(it);
		}
		return *this;
	}

	FDeque<T> &operator*=(const FDeque<T> &rhs) {
		auto dit = this->data;
		for(auto sit = this->data; sit != this->dataEnd; sit++) {
			if(rhs.contains(*sit)) {
				*dit++ = *sit;
			} 
		}
		this->dataEnd = dit;
		return *this;
	}

	const FDeque<T> operator+(const FDeque<T> &rhs) const {
		return FDeque<T>(*this) += rhs;
	}

	const FDeque<T> operator*(const FDeque<T> &rhs) const {
		return FDeque<T>(*this) *= rhs;
	}

	/**
	 * equal \iff both deques contain same elements in same order
	 */
	bool operator==(const FDeque<T> &rhs) const {
		if (this->length() != rhs.length())
			return false;
		for (auto lh = this->begin(), rh = rhs.begin(); lh != this->end(); lh++, rh++)
			if (*lh != *rh)
				return false;
		return true;
	}

	bool operator!=(const FDeque<T> &rhs) const {
		return !(*this == rhs);
	}

	/**
	 * move constructor
	 */
	FDeque(FDeque<T> &&o) noexcept : FDeque(o.currentCapacity) {
		swap(*this, o);
	}

	/**
	 * copy constructor, strong exception guarantee unless T::operator= throws
	 */
	FDeque(const FDeque<T> &o) : FDeque(o.currentCapacity) {
		for(auto it = o.data; it != o.dataEnd; it++) {
			*this->dataEnd++ = *it;
		}
	};

	FDeque(int capacity = 64) :
			currentCapacity(capacity) {
		dataEnd = data = new T[this->currentCapacity];
		list_number++;
	}

	FDeque<T> &operator=(const FDeque<T> rhs) {
		swap(*this, rhs);
		return *this;
	}

	~FDeque() noexcept {
		delete[] this->data;
		this->data = nullptr;
		list_number--;
	}

	const unsigned long length() const {
		return dataEnd - data;
	}

private:
	static int list_number;

	static void swap(FDeque<T> &lhs, FDeque<T> &rhs) {
		using std::swap;
		swap(lhs.data, rhs.data);
		swap(lhs.dataEnd, rhs.dataEnd);
		swap(lhs.currentCapacity, rhs.currentCapacity);
	}

	T *data;
	T *dataEnd;
	int currentCapacity;
};

/**
 * no need to use private part, so standalone version
 */
template<typename T>
std::ostream &operator<<(std::ostream &os, const FDeque<T> &self) {
	os << "Matrix <" << typeid(T).name() << "> " << &self<< std::endl;
	for (auto it : self) {
		os << "[" << &it << "] :\n"  << it ;
	}
		return os;
	}


/**
 * list counter
 */
template<typename T>
int FDeque<T>::list_number = 0;

