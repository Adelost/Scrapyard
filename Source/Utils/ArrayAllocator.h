#pragma once

#include "Memory.h"

namespace ae
{
template<class T>
class ArrayAllocator
{
public:
	ArrayAllocator()
	{
		elements = nullptr;
		count = 0;
		capacity = 0;
	}

	ArrayAllocator(int size)
	{
		elements = new T[size];
		count = size;
		capacity = size;
	}

	void add()
	{
	}

	void addRaw(int count = 1)
	{
		resize(count + count);
	}

	void removRaw(int index)
	{

	}

	/// Constructs element at index.
	void construct(const T& element, int index)
	{
		Memory::construct(element, elements[count]);
	}

	/// Destructs element at index.
	void destruct(int index)
	{
		Memory::destroy(elements[index]);
	}

	void reserve(int size)
	{
		if (size > capacity)
		{
			if (capacity < 1)
				capacity = 1;
			while (capacity < size)
				capacity *= 2;

			T* tmp = Memory::allocate<T>(capacity);
			Memory::copy(&elements[0], &tmp[0], count);
			Memory::deallocate(elements);
			elements = tmp;
		}
	}

	void reserveExact(int size)
	{
		if (size > capacity)
		{
			capacity = size;

			T* tmp = Memory::allocate(capacity);
			Memory::copy(elements[0], tmp[0], count);
			Memory::deallocate(elements);
			elements = tmp;
		}
	}

public:
	T* elements;
	int count;
	int capacity;
};

