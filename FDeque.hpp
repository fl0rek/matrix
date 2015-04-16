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

		iterator();

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
		return iterator(this->iStart);
	}

	iterator end() {
		return iterator(this->iEnd);
	}


	FDeque<T> &operator+=(const FDeque<T> &);

	FDeque<T> &operator*=(const FDeque<T> &);

	const FDeque<T> operator+(const FDeque<T> &rhs) const {
		return FDeque<T>(*this) += rhs;
	}

	const FDeque<T> operator*(const FDeque<T> &rhs) const {
		return FDeque<T>(*this) *= rhs;
	}

	bool operator==(const FDeque<T> &) const;

	bool operator!=(const FDeque<T> &rhs) const {
		return !(*this == rhs);
	}

	FDeque(FDeque<T> &&o) : FDeque(o.currentCapacity) {
		swap(*this, o);
	}

	FDeque(const FDeque<T> &o) : FDeque(o.currentCapacity, 0, o.length()) {
		this->data = new T[this->currentCapacity];
		if(o.iStart < o.iEnd) {
			std::copy(o.data +o.iStart, o.data +o.iEnd, this->data);
		} else {
			auto end = std::copy(o.data +o.iEnd, o.data +o.currentCapacity-1, this->data);
			std::copy(o.data, o.data +o.iStart, end);
		}
	};

	FDeque(int capacity = 64, int startingElement = 0, int endingElement = 0 ) :
			iStart(startingElement), iEnd(endingElement), currentCapacity(capacity) {
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
		int ret = this->iEnd - this->iStart;
		return ret >= 0 ? ret : this->currentCapacity + ret;
	}

	template<class TT>
	friend std::ostream &operator<<(std::ostream &os, FDeque<TT> &self) {
		for (auto it : self) {
			os << typeid(it).name();
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
	int currentCapacity;

	int iStart;
	int iEnd;
};

