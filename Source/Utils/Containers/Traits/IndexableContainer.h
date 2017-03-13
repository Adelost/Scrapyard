#pragma once

#include "../../_old/Cast.h"
#include "../../Memory.h"
#include "../../XAssert.h"


/// Groups
template<class T>
class Allocator
{
public:
	/// Standard allocation of
	class Standard
	{
		static void construct(const T& object, T& destination)
		{
			Memory::construct(object, destination)
		}

		static void destruct(T& object)
		{
			Memory::destruct(object)
		}
		static T* allocate(int count)
		{
			Memory::destruct(object)
		}
		static void deallocate(T object)
		{
		}
	};
	/// Only allocates memory for elements, skips calling constructor and destructor.
	class Raw
	{
		void construct(const T& object, T& destination)
		{
		}
		void destruct(T& object)
		{
		}
	};
};

// T_Constructor = Constructor::Normal<T>
#include <Utils/Console.h>

template<class T>
class ArrayBase
{
public:
	ArrayBase()
	{
		ae::print() << "LA Constructor";

		m_elements = nullptr;
		m_count = 0;
		m_capacity = 0;
	}

	
	~ArrayBase()
	{
		clearMemory();
	}

	/// Removes all elements.
	void clear()
	{
		for (int i = count() - 1; i >= 0; i--)
			at(i).~T();
		m_count = 0;
	}

	/// Removes all elements and releases any allocated memory.
	void clearMemory()
	{
		clear();

		Memory::deallocate(m_elements);
		m_elements = nullptr;
		m_capacity = 0;
	}


	/// Adds an element to the container.
	void add(const T& element)
	{
		reserve(m_count + 1);
		Memory::construct(element, m_elements[m_count]);
		m_count++;
	}

	/// If "size" exceeds capacity, more memory is allocated until
	/// capacity is enough to hold "size" elements.
	void reserve(int size)
	{
		if (size > m_capacity)
		{
			if (m_capacity < 1)
				m_capacity = 1;
			while (m_capacity < size)
				m_capacity *= 2;

			T* tmp = Memory::allocate<T>(m_capacity);
			Memory::copy(&m_elements[0], &tmp[0], m_count);
			Memory::deallocate(m_elements);
			m_elements = tmp;
		}
	}

	/// Resized the container so that it contains "size" elements constructed with default constructor.
	void resize(int size)
	{
		if (size > m_count)
		{
			reserve(size);

			for (int i = m_count; i < m_count; i++)
				Memory::construct(T(), m_elements[i]);

			m_count = size;
		}
	}

	/// Returns element at the specified index.
	T& at(int index)
	{
		return CALL_CONST_METHOD_AS_NON_CONST(at(index));
	}

	const T& at(int index) const
	{
		xassert_msg(isInside(index), "Index out of bounds.");
		return m_elements[index];
	}

	/// Returns the number of stored elements.
	int count() const
	{
		return m_count;
	}

	/// Returns the number of elements the array can contain before
	/// needing to resize.
	int capacity() const
	{
		return m_capacity;
	}

	/// Returns the index of an element inside the container. Element
	/// must already be residing inside the container. Useful in some
	/// rare situations where an element do not know its index.
	int indexFromElement(T* element)
	{
		int index = static_cast<int>(&m_values[0] - &value);
		xassert_msg(isInside(index), "Element do not reside inside container.");
		return index;
	}

	/// Checks if "index" is within the boundaries of the array.
	bool isInside(int index) const
	{
		return index >= 0 && index < count();
	}

	/// Checks if "index" is within the boundaries of the array.
	bool copy(int index) const
	{
		return index >= 0 && index < count();
	}


private:
	T* m_elements;
	int m_count;
	int m_capacity;
};

/// Implements functionality shared by all index-based containers.
///
/// It implements an iterator, copy constructor, assignment operator,
/// and convenience methods.
///
/// To be considered an index-based container, the specified "T_Base"
/// must contain the following methods:
/// - add(T)
/// - at(int)
/// - count()
/// - capacity()
/// - resize(int)
/// - reserve(int)
/// - clear()
template<class T, class T_Base>
class IndexableTrait : public T_Base
{
public:
	/// Asserts that all methods to be considered an index-based
	/// container is implemented. Causes a compilation error if not.
	void assertIndexableContainer()
	{
		IndexableContainer c;
		c.add(T());
		c.at(0);
		c.count();
		c.capacity();
		c.resize(1);
		c.reserve(1);
		c.clear();
	}

	IndexableContainer()
	{
	}

	/// Constructs a copy of "other".
	IndexableContainer(const IndexableContainer& other) : T_Base()
	{
		*this = other;
	}

	/// Copies the elements of "other" to this container, replacing
	/// its current content, and modifying its size accordingly.
	IndexableContainer& operator=(const IndexableContainer& other)
	{
		clear();
		for (int i = 0; i < count(); i++)
			at(i) = other.at(i);
		return *this;
	}

	/// Same as add(), overloading stream operator allows adding
	/// multiple elements.
	IndexableContainer& operator<<(const T& element)
	{
		add(element);
		return *this;
	}

	/// Returns element at the specified index.
	T& operator[](int index)
	{
		return CALL_CONST_METHOD_AS_NON_CONST(operator[](index));
	}
	const T& operator[](int index) const
	{
		return at(index);
	}

	/// Adds multiple element to the container from any iterable container.
	template<class T_Iterable>
	void addAll(const T_Iterable& container)
	{
		for (T& e : container)
			add(e);
	}
	/// Adds multiple element to the container from a pointer to an
	/// array.
	void addAll(const T* elements, int count)
	{
		reserve(count() + count);
		for (int i = 0; i < count; i++)
			add();
		m_count += count;
	}


	/// Returns true if array contains no elements.
	bool isEmpty() const
	{
		return count() == 0;
	}

	/// Returns true if array contains no elements.
	bool isNotEmpty() const
	{
		return !isEmpty();
	}

	/// Returns true if adding another element will cause the array to
	/// resize.
	bool isFull() const
	{
		return count() >= capacity();
	}

	/// Returns the first item.
	T& first()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(first());
	}
	const T& first() const
	{
		return at(0);
	}

	/// Returns the last item.
	T& last()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(last());
	}
	const T& last() const
	{
		return at(count() - 1);
	}

	/// Fast removal of element by swapping the last element with the
	/// element deleted.
	void swapRemove(int index)
	{
		xassert_msg(!isEmpty(), "No elements to remove.");
		at(index).~T();
		Memory::copy(&m_elements[m_count - 1], &m_elements[index], 1);
		m_count--;
	}

public:
	class Iterator
	{
	public:
		Iterator(IndexableContainer* host, int index)
		{
			m_host = host;
			m_index = index;
		}
		void reset()
		{
			m_index = 0;
		}
		bool operator!=(const Iterator& other) const
		{
			return m_index != other.m_index;
		}
		const Iterator& operator++()
		{
			m_index++;
			return *this;
		}
		T& operator*() const
		{
			return (*m_host)[m_index];
		}

	private:
		IndexableContainer* m_host;
		int m_index;

	};
	Iterator begin()
	{
		return begin(0);
	}
	Iterator end()
	{
		return end(count());
	}
};

template<class T, class T_Base = ArrayBase<T>>
class SomeArray : public IndexableContainer<T, T_Base>
{
};

template<class T, class T_Base = ArrayBase<T>>
class SomeArray : public IndexableContainer<T, IndexableContainer<T, T>>
{
};