#pragma once

#include <ostream>

//
// Allows outputting various classes using standard ostream.
//

#include <vector>
/// Prints all elements of a std::vector.
template<class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& data)
{
	os << "[";
	for (size_t i = 0; i < data.size() - 1; i++)
		os << data[i] << ", ";
	if (!data.empty())
		os << data.back();
	os << "]";

	return os;
}