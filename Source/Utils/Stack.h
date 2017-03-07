#pragma once

#include "Array.h"

namespace ae
{
template<class T>
class Stack
{
public:
	void push(T& element)
	{
		m_elements.add(element);
	}

	T pop()
	{
		T e = m_elements.last();
		m_elements.removeLast();

		return e;
	}

	T& peek()
	{
		return m_elements.last();
	}

	void isEmpty()
	{
		return m_elements.isEmpty();
	}

private:
	Array<T> m_elements;
};
}
