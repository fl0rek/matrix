#pragma once

#include "commons.h"

#include <typeinfo>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>

template<typename T>
class FDeque {
public:
	typedef typename T::value_type value_type;
	typedef typename T::reference reference;
	typedef typename T::const_reference const_reference;
	typedef typename T::difference_type difference_type;
	typedef typename T::size_type size_type;

	class const_iterator {
	public:
		typedef typename T::difference_type difference_type;
		typedef typename T::value_type value_type;
		typedef typename T::const_reference reference;
		typedef typename T::const_pointer pointer;
		typedef std::bidirectional_iterator_tag iterator_category;

		const_iterator &operator=(const const_iterator rhs) {
			this->ptr = rhs.ptr;
			return *this;
		}

		const_iterator &operator++() {
			this->ptr++;
			return *this;
		}

		const_iterator operator++(int) const {
			const_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		const_iterator &operator--() {
			this->ptr--;
			return *this;
		}

		const_iterator operator--(int) const {
			const_iterator tmp(*this);
			++(*this);
			return tmp;
		}


		reference operator*() const {
			return *ptr;
		}

		pointer operator->() const {
			return ptr;
		}

		bool operator==(const_iterator const &rhs) const {
			return this->ptr == rhs.ptr;
		}

		bool operator!=(const_iterator const &rhs) const {
			return !(*this == rhs);
		}

		const_iterator(T ptr) : ptr(ptr) { }

		const_iterator(const_iterator &rhs) : ptr(rhs.ptr) {
		}

		~const_iterator() {

		};

	private:
		T* ptr;
	};


	const_iterator begin() const {
		return const_iterator(this->data);
	}

	const_iterator end() const {
		return const_iterator(this->dataEnd);
	}

	bool contains(T & el) const {
		for(auto it = this->data; it != this->dataEnd; it++) {
			if(*it == el)
				return true;
		}
		return false;
	}

	FDeque<T> &resize(int newSize) {
		unsigned long offset = this->dataEnd - this->data;
		T* newdata = new T[newSize];
		std::copy(this->data, this->dataEnd, newdata);
		delete [] data;
		this->data = newdata;
		this->dataEnd = newdata + offset;
		return *this;
	}

	FDeque<T> &operator+=(const T & rhs) {
		if(this->length()-1 >= this->currentCapacity) {
			this->resize(this->currentCapacity *2);
		}
		*(this->dataEnd++) = rhs;
		return *this;
	}

	FDeque<T> &operator+=(const FDeque<T> & rhs) {
		for(auto it : rhs) {
			*this += it;
		}
		return *this;
	}

	FDeque<T> &operator*=(const FDeque<T> & rhs) {
		for(auto it : rhs) {
			*this -= it;
		}
		return *this;
	}

	FDeque<T> &operator-=(const T & rhs) {
		this->data = std::remove(this->data, this->dataEnd, rhs);
		return *this;
	}

	const FDeque<T> operator+(const FDeque<T> &rhs) const {
		return FDeque<T>(*this) += rhs;
	}

	const FDeque<T> operator*(const FDeque<T> &rhs) const {
		return FDeque<T>(*this) *= rhs;
	}

	const FDeque<T> operator-(const T & rhs) const {
		return FDeque<T>(*this) -= rhs;
	}

	bool operator==(const FDeque<T> &rhs) const {
		if(this->length() != rhs.length())
			return false;
		for(auto lh = this->begin(), rh = rhs.begin(); lh != this->end(); lh++, rh++) 
			if(*lh != *rh)
				return false;
		return true;
	}

	bool operator!=(const FDeque<T> &rhs) const {
		return !(*this == rhs);
	}

	FDeque(FDeque<T> &&o) : FDeque(o.currentCapacity) {
		swap(*this, o);
	}

	FDeque(const FDeque<T> &o) : FDeque(o.currentCapacity) {
		std::copy(o.data, o.dataEnd, this->data);
	};

	FDeque(int capacity = 64) :
			currentCapacity(capacity) {
		data = new T[this->currentCapacity];
		list_number++;
	}

	FDeque<T> &operator=(const FDeque<T> rhs) {
		swap(*this, rhs);
		return *this;
	}

	~FDeque() {
		delete [] data;
		list_number--;
	}

	const unsigned long length() const {
		return dataEnd - data -1; 
	}

	template<class TT>
	friend std::ostream &operator<<(std::ostream &os, const FDeque<TT> &self) {
		for (auto it : self) {
			os << it;
		}
		return os;
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

template <typename T>
int FDeque<T>::list_number = 0;

