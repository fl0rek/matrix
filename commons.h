#pragma once 

#include <memory>

#ifndef D
# ifdef _DEBUG
#  define D(x) x
# else 
#  define D(x)
# endif
#endif

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

