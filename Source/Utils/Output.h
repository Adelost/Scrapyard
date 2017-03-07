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

#include "Array.h"
/// Prints all elements of an Array.
template<class T>
std::ostream& operator << (std::ostream& os, const ae::Array<T>& data)
{
	os << "[";
	for (int i = 0; i < data.count() - 1; i++)
		os << data[i] << ", ";
	if (!data.isEmpty())
		os << data.last();
	os << "]";

	return os;
}

#include "PoolArray.h"
/// Prints all elements of a PoolArray.
template<class T>
std::ostream& operator << (std::ostream& os, const ae::PoolArray<T>& data)
{
	int count = data.count();
	os << "[";
	for (int i = 0; i < count; i++)
	{
		if (!data.isGap(i))
			os << data[i];
		else
			os << "#";

		if (i != count - 1)
			os << ", ";
	}
	os << "]";

	return os;
}
