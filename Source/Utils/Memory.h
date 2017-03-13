#pragma once

#include <cstdlib>

namespace ae
{
/// Makes managing memory in an application more convenient.
/// 
/// TODO:
///	- Investigate "calloc", 
class Memory
{
public:
	/// Makes binary copies of "count" elements from source to destination.
	/// To avoid overflows, the memory blocks should not overlap (for
	/// overlapping memory blocks, move() is a safer approach).
	template<class T>
	static void copy(const T* source, T* destination, int count);
	/// Same as copy(), but copies bytes instead of whole elements.
	static void copyRaw(const void* source, void* destination, int bytes);
	/// Similar to copy(), but allows source and destination to overlap.
	template<class T>
	static void move(const T* source, T* destination, int count);
	/// Same as move() but copies bytes instead of whole elements.
	static void moveRaw(const void* source, void* destination, int bytes);
	
	/// Allocates a uninitialized block of memory big enough to contain
	/// "count" elements. Caller is responsible for freeing the memory
	/// later using deallocate().
	template<class T>
	static T* allocate(int count);
	/// Deallocates memory block without calling any destructor.
	static void deallocate(void* data);
	/// Constructs an object on already allocated memory. Useful
	/// during custom memory allocation. Same as a "placement
	/// new".
	template<class T>
	static void construct(const T& object, T& destination);
	/// Calls the destructor on an object. See also construct().
	template<class T>
	static void destruct(T& object);
};

template<class T>
void Memory::copy(const T* source, T* destination, int count)
{
//	copyRaw(source, destination, count * sizeof(T));
}

template<class T>
void Memory::move(const T* source, T* destination, int count)
{
	moveRaw(source, destination, count * sizeof(T));
}

template<class T>
T* Memory::allocate(int count)
{
	return static_cast<T*>(malloc(count * sizeof(T)));
}

template<class T>
void Memory::construct(const T& object, T& destination)
{
	new(&destination)T(object);
}

template<class T>
void Memory::destruct(T& object)
{
	object.~T();
}
}