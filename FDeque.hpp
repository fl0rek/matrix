#pragma once

#include "Node.h"

#include <typeinfo>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


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
		iterator(const iterator&);
		~iterator();

		iterator& operator=(const iterator&);

		iterator &operator++() {
			this->n = n->n;
			return *this;
		}
		iterator operator++(int) const {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}

		iterator &operator--() {
			this->n = n->p;
			return *this;
		}
		iterator operator--(int) const {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}


		reference operator*() const {
			return (n->data).get();
		}
		pointer operator->() const {
			return (n->data).get();
		}

		bool operator==(iterator const& rhs) const {
			return this->n == rhs.n;
		}
		bool operator!=(iterator const& rhs) const {
			return !(*this == rhs);
		}

		iterator(std::shared_ptr<Node<T>> rhs) : n(rhs) { }
		iterator(iterator &rhs) {
			n = std::make_shared(rhs.n);
		}

	private:
		std::shared_ptr<Node<T>> n;
	};


	iterator begin() {
		return iterator(this->p_start);
	}
	iterator end() {
		return iterator(this->p_end);
	}


	FDeque<T>& operator+=(const FDeque<T> &);
	FDeque<T>& operator*=(const FDeque<T> &);

	const FDeque<T> operator+(const FDeque<T> &) const;
	const FDeque<T> operator*(const FDeque<T> &) const;

	bool operator==(const FDeque<T> &) const;
	bool operator!=(const FDeque<T> &) const;

	FDeque<T>(FDeque<T> &&);
	FDeque<T>(const FDeque<T> &);
	FDeque<T>() :
			p_start(nullptr), p_end(nullptr) {
		list_number++;
	}

	FDeque<T>& operator=(const FDeque<T>);

	~FDeque<T>() {
		list_number--;
	}

	template<class TT>
	friend std::ostream& operator<<(std::ostream &os, FDeque<TT> &self) {
		for(auto it : self) {
			os << typeid(it).name();
		}
		return os;
	}
private:
	static int list_number;
	static void swap(FDeque<T> &, FDeque<T> &);

	std::shared_ptr<Node<T>> p_start;
	std::shared_ptr<Node<T>> p_end;
	std::shared_ptr<Node<T>> current;
};

