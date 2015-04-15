#pragma once

#include "Node.h"

#include <bits/stl_iterator_base_types.h>
#include <cstddef>
#include <memory>

template<typename T, typename T_nonconst = typename std::remove_const<T>::type,
		typename elem_type = typename T::value_type>
class FDequeIterator {
public :
	typedef FDequeIterator<T, T> self_type;
	typedef T FDequeType;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T &reference;
	typedef const T &const_reference;

	elem_type operator*() const {
		return n;
	}
	elem_type operator->() const {
		return n.get();
	}

	self_type &operator++() {
		this->n = n->n;
		return *this;
	}
	self_type operator++(int) {
		self_type tmp(*this);
		++(*this);
		return tmp;
	}

	self_type &operator--() {
		this->n = n->p;
		return *this;
	}
	self_type operator--(int) {
		self_type tmp(*this);
		++(*this);
		return tmp;
	}

	bool operator==(FDequeIterator<T> const& rhs) const {
		return this->n == rhs.n;
	}
	bool operator!=(FDequeIterator<T> const& rhs) const {
		return !(*this == rhs);
	}

	FDequeIterator(std::shared_ptr<Node<T>> rhs) : n(rhs) { }
	FDequeIterator(FDequeIterator<T> &rhs) {
		n = std::make_shared(rhs.n);
	}
	FDequeIterator(const FDequeIterator<T_nonconst, T_nonconst, typename T_nonconst::value_type> &rhs) {

	}
private :
	std::shared_ptr<Node<T>> n;
};

