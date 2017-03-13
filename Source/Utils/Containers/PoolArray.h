#pragma once

#include "PoolArrayBase.h"
#include "List.h"



namespace ae
{
/// Container structure that is a mix between a pool allocator and a
/// dynamic array. It is useful when fast allocation and deallocation
/// of elements is needed. Adding and removing elements is O(1)
/// average and O(n) worst case.
/// 
/// It works by the same principle as a pool allocator. Same size
/// elements are allocated in a preallocated memory block. But the
/// structure can also be traversed linearly, as an array, as compared
/// to a more common linked list approach. An iterator is needed to
/// traverse the values stored inside, as the array may contain gaps.
template <class T>
using PoolArray = PoolArrayBase<T, Array<T>>;
}