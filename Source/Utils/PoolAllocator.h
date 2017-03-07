#pragma once

#include "XAssert.h"
#include <iostream>

#include "Array.h"
#include "Stack.h"
#include "Memory.h"

namespace ae
{
template<class T>
class PoolAllocator
{
public:
	PoolAllocator()
	{
	}

	void add(T* element)
	{
		if(m_gaps.isEmpty())
			m_elements.add(element);
		else
			m_elements[m_gaps.pop()] = element;
	}

	void remove(int index)
	{
		m_gaps.add(index);
	}

	void deallocate()
	{
		m_gaps.remove(element);
	}

	void construct()
	{
	}

	void destroy()
	{
	}

private:
	Array<T> m_elements;
	Stack<int> m_gaps;
};
}