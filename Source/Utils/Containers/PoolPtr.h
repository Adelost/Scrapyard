#pragma once

#include "StablePoolArray.h"
#include "../XAssert.h"

namespace ae
{
/// Allows fast allocation of objects. This is usually much faster than
/// standard allocation using "new" and "delete".
/// 
/// Objects should be instantiated with the class similarly to using a
/// smart pointer. Instantiated objects should also be deleted
/// afterwards using the "release()" method.
template<class T>
class PoolPtr
{
public:
	PoolPtr() {}

	PoolPtr(const T& object)
	{
		*this = object;
	}

	PoolPtr& operator=(const T& object)
	{
		set(object);

		return *this;
	}

	/// Allocates and assigns a copy of the specified object.
	void set(const T& object)
	{
		m_index = s_pool.add(object);
	}

	/// Releases the current, all assigned.
	void release()
	{
		s_pool.remove(m_index);
	}

	T& get()
	{
		return s_pool[m_index];
	}

	T& operator*()
	{
		return get();
	}

	T* operator->()
	{
		return &get();
	}

	/// Preallocate memory for "size" number of elements to make
	/// allocation faster.
	static void Reserve(int size)
	{
		s_pool.reserve(size);
	}

private:
	class Allocator : public StablePoolArray<T>
	{
	public:
		~Allocator()
		{
			xassert_msg(s_pool.isEmpty(),
			            "Some elements allocated by PoolPtr has not been released.");
		}
	};
	static Allocator s_pool;
	int m_index;
};

template<class T>
typename PoolPtr<T>::Allocator PoolPtr<T>::s_pool;
}