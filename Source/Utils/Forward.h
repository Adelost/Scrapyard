#pragma once
#include <type_traits>
namespace ae
{
template<class T>
T&& forward(typename std::remove_reference<T>::type& arg)
{
	return static_cast < T && >(arg)
}
}
