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

	class iterator {
	public:
		typedef typename T::difference_type difference_type;
		typedef typename T::value_type value_type;
		typedef typename T::reference reference;
		typedef typename T::pointer pointer;
		typedef std::bidirectional_iterator_tag iterator_category;

		iterator &operator=(const iterator rhs) {
			this->ptr = rhs.ptr;
			return *this;
		}

		iterator &operator++() {
			this->ptr++;
			return *this;
		}

		iterator operator++(int) const {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}

		iterator &operator--() {
			this->ptr--;
			return *this;
		}

		iterator operator--(int) const {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}


		reference operator*() const {
			return *ptr;
		}

		pointer operator->() const {
			return ptr;
		}

		bool operator==(iterator const &rhs) const {
			return this->ptr == rhs.ptr;
		}

		bool operator!=(iterator const &rhs) const {
			return !(*this == rhs);
		}

		iterator(T ptr) : ptr(ptr) { }

		iterator(iterator &rhs) : ptr(rhs.ptr) {
		}

		~iterator() {

		};

	private:
		T* ptr;
	};


	iterator begin() {
		return iterator(this->data);
	}

	iterator end() {
		return iterator(this->dataEnd);
	}

	bool contains(T & el) const {
		for(auto it : this->data) {
			if(*it == el)
				return true;
		}
		return false;
	}

	FDeque<T> &resize(int newSize) {
		int offset = this->dataEnd - this->data;
		T* newdata = new T[newSize];
		std::copy(this->data, this->dataEnd, newdata);
		delete [] data;
		this->data = newdata;
		this->dataEnd = newdata + offset;
		return this;
	}

	FDeque<T> &operator+=(const T & rhs) {
		if(this.length()-1 >= this->currentCapacity) {
			this->resize(this->currentCapacity *2);
		}
		this->dataEnd++ = rhs;
		return this;
	}

	FDeque<T> &operator+=(const FDeque<T> & rhs) {
		for(auto it : rhs) {
			*this += it;
		}
	}

	FDeque<T> &operator*=(const FDeque<T> & rhs) {
		for(auto it : rhs) {
			*this -= it;
		}
	}

	FDeque<T> &operator-=(const T & rhs) {
		auto removed = *el;
		this->data = std::remove(this->data, this->dataEnd, removed);
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
		for(auto lh = this->begin(), auto rh = rhs.begin(); lh != this->end(); lh++, rh++) 
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

	const int length() const {
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
		swap(lhs.currentCapacity, rhs.currentCapacity);
		swap(lhs.iStart, rhs.iStart);
		swap(lhs.iEnd, rhs.iEnd);

	}

	T *data;
	T *dataEnd;
	int currentCapacity;
};

