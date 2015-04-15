#pragma once
#include <memory>
template <class T>
class Node {
public:
	Node(std::shared_ptr<T> d, std::shared_ptr<Node<T>> p, std::shared_ptr<Node<T>> n)
			: data(d), p(p), n(n) {}
	std::shared_ptr<T> data;
	std::shared_ptr<Node<T>> p;
	std::shared_ptr<Node<T>> n;
};
