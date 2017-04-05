#pragma once

#include "Cast.h"
#include "Memory.h"
#include "Assert.h"
#include "Algorithm.h"
#include "Math.h"

#include <initializer_list>
#include <string>

namespace ae {
/// A resizable container, which stores elements in adjacent memory
/// locations and provides a fast index-based lookup.
///
/// It is many ways similar to std::vector, but has a more readable
/// implementation and additional convenience methods.
///
/// - Elements are reallocated when growing, causing any pointers
///   pointing to elements inside the container to become invalidated.
/// - Does not allocate on heap until a first element is added to it.
/// - Supports C++11 iterators to make iterating more convenient.
/// - Allows adding multiple elements on a single line using the
///   output stream operator (<<).
/// - Provides out of bound checking in debug.
template<class T>
class List {
public:
    /// Constructs an empty container.
    List() {
        m_elements = nullptr;
        m_count = 0;
        m_capacity = 0;
    }
    /// Move constructor.
    List(List&& other) {
        m_elements = other.m_elements;
        m_count = other.m_count;
        m_capacity = other.m_capacity;
        other.m_elements = nullptr;
        other.m_count = 0;
        other.m_capacity = 0;
    }
    /// Initializer list constructor.
    List(std::initializer_list<T> list) : List() {
        reserve((int) list.size());
        addAll(list);
    }
    /// Constructs an Array from any iterable
    /// container.
    template<class T_Iterable>
    List(const T_Iterable& container) : List() {
        addAll(container);
    }
    List<T>& operator=(std::initializer_list<T> list) {
        return *this;
    }
    /// Constructs an Array with an initial size of "size" elements
    /// constructed using default constructor.
    List(int size) {
        m_elements = new T[size];

        m_count = size;
        m_capacity = size;
    }
    /// Constructs a copy of "other".
    List(const List<T>& other) : List() {
        *this = other;
    }
    /// Destroys the container and all elements.
    ~List() {
        clearMemory();
    }
    /// Copies the elements of "other" to this container, replacing
    /// its current contents, and modifying its size accordingly.
    List<T>& operator=(const List<T>& other) {
        clear();
        addAll(other.raw(), other.count());

        return *this;
    }
    /// Same as add(), overloading stream operator allows adding
    /// multiple elements.
    List<T>& operator<<(const T& element) {
        add(element);

        return *this;
    }
    /// Returns element at the specified index.
    T& operator[](int index) {
        return CALL_CONST_METHOD_AS_NON_CONST(operator[](index));
    }
    const T& operator[](int index) const {
        xassert_msg(isInside(index), "Index out of bounds.");
        return m_elements[index];
    }
    /// Adds an element to the container.
    void add(const T& element) {
        reserve(m_count + 1);
        Memory::construct<T>(element, m_elements[m_count]);
        m_count++;
    }
    /// Adds multiple element to the container from a pointer to an
    /// array.
    void addAll(const T* elements, int count) {
        reserve(m_count + count);
        for (int i = 0; i < count; i++)
            Memory::construct(elements[i], m_elements[m_count + i]);
        m_count += count;
    }
    /// Adds multiple element to the container from any iterable
    /// container.
    template<class T_Iterable>
    void addAll(const T_Iterable& container) {
        for (const T& e : container)
            add(e);
    }
    /// Inserts an element at specified index. Subsequent elements are
    /// transposed to cover the resulting gap, which may be a slow
    /// operation depending of the number of elements.
    void insertAt(int index, const T& element) {
        insertAt(index, &element, 1);
    }
    /// Adds an uninitialized elements.
    void addRaw(int count = 1) {
        resize(m_count + count);
    }
    /// Same as addAt() but allows adding multiple elements.
    void insertAt(int index, const T* elements, int count) {
        // Shift elements right to create a gap
        reserve(m_count + count);
        int size = m_count - index;
        Memory::move(&m_elements[index], &m_elements[index + count], size);

        // Add elements
        for (int i = 0; i < count; i++)
            Memory::construct(elements[i], m_elements[index + i]);
        m_count += count;
    }
    /// Removes the last element.
    void removeLast() {
        xassert_msg(!isEmpty(), "No elements to remove.");
        last().~T();
        m_count--;
    }
    /// Removes element at index. Subsequent elements are transposed
    /// to cover the resulting gap. See also addAt().
    void removeAt(int index) {
        removeAt(index, 1);
    }
    /// Same as removeAt() but allows removing multiple elements.
    void removeAt(int index, int count) {
        xassert_msg(m_count - count >= 0, "No elements to remove.");

        // Remove elements
        for (int i = 0; i < count; i++)
            m_elements[index + i].~T();
        m_count -= count;

        // Shift right segment left to cover gap
        int rightSize = m_count - index;
        Memory::move(&m_elements[index + count], &m_elements[index],
                     rightSize);
    }
    /// Fast removal of element by swapping the last element with the
    /// element deleted.
    void swapRemove(int index) {
        xassert_msg(!isEmpty(), "No elements to remove.");
        m_elements[index].~T();
        Memory::copy(&m_elements[m_count - 1], &m_elements[index], 1);
        m_count--;
    }
    /// Removes all elements.
    void clear() {
        for (int i = count() - 1; i >= 0; i--)
            m_elements[i].~T();
        m_count = 0;
    }
    /// Removes all elements and releases any allocated memory.
    void clearMemory() {
        clear();
        clearMemoryRaw();
    }
    /// Removes all elements and releases any allocated memory calling destructor.
    void clearMemoryRaw() {
        Memory::deallocate(m_elements);
        m_count = 0;
        m_elements = nullptr;
        m_capacity = 0;
    }
    /// If "size" exceeds capacity, more memory is allocated until
    /// capacity is enough to hold "size" elements.
    void reserve(int size) {
        if (size > m_capacity) {
            if (m_capacity < 1)
                m_capacity = 1;
            while (m_capacity < size)
                m_capacity *= 2;

            T* tmp = Memory::allocate<T>(m_capacity);
            Memory::copy<T>(m_elements, tmp, m_count);
            Memory::deallocate(m_elements);
            m_elements = tmp;
        }
    }
    /// Same as reserve(), except that the growth in capacity is
    /// limited to exactly "size" elements. This allows saving memory
    /// in some situation.
    void reserveExact(int size) {
        if (size > m_capacity) {
            m_capacity = size;
            T* tmp = Memory::allocate<T>(m_capacity);
            Memory::copy<T>(&m_elements[0], &tmp[0], m_count);
            Memory::deallocate(m_elements);
            m_elements = tmp;
        }
    }
    /// Resized the container so that it contains "size" elements. New
    /// elements are uninitialized.
    void resize(int size) {
        if (size > m_count) {
            reserve(size);
            for (int i = m_count; i < m_count; i++) {
                Memory::construct(T(), m_elements[i]);
            }
            m_count = size;
        }
    }
    /// Returns the index of an element inside the container. Element
    /// must already be residing inside the container. Useful in some
    /// rare situations where an element do not know its index.
    int indexFromElement(T* element) {
        int index = static_cast<int>(&m_elements[0] - &element);
        xassert_msg(isInside(index),
                    "Element do not reside inside container.");
        return index;
    }
    /// Constructs element at index.
    void construct(const T& element, int index) {
        Memory::construct(element, m_elements[m_count]);
    }
    /// Destructs object at index.
    void destruct(int index) {
        Memory::destruct(m_elements[index]);
    }
    /// Returns the first item.
    T& first() {
        return CALL_CONST_METHOD_AS_NON_CONST(first());
    }
    const T& first() const {
        return (*this)[0];
    }
    /// Returns the last item.
    T& last() {
        return CALL_CONST_METHOD_AS_NON_CONST(last());
    }
    const T& last() const {
        return (*this)[m_count - 1];
    }
    /// Exposes the raw pointer storing the elements of the container.
    /// The pointer can be used to modify elements and remains valid
    /// as long as the container is not reallocated.
    T* raw() {
        return CALL_CONST_METHOD_AS_NON_CONST(raw());
    }
    const T* raw() const {
        return m_elements;
    }
    /// Returns the number of stored elements.
    int count() const {
        return m_count;
    }
    /// Alternative syntax for count()
    int size() const {
        return count();
    }
    /// Returns the number of elements the array can contain before
    /// needing to resize.
    int capacity() const {
        return m_capacity;
    }
    /// Returns true if array contains no elements.
    bool isEmpty() const {
        return m_count == 0;
    }
    /// Returns true if adding another element will cause the array to
    /// resize.
    bool isFull() const {
        return m_count >= m_capacity;
    }
    /// Checks if "index" is within the boundaries of the array.
    bool isInside(int index) const {
        return index >= 0 && index < count();
    }
    /// Joins the elements of an array into a string.
    std::string join(std::string separator = ",") const {
        if (isEmpty()) {
            return "";
        }
        std::string joined = "";
        for (int i = 0; i < count() - 1; i += 1) {
            joined += std::to_string((*this)[i]);
            joined += separator;
        }
        joined += std::to_string(last());
        return joined;
    }
    /// Returns a string representation of the list.
    std::string toString() const {
        return "[" + join(", ") + "]";
    }
    /// Creates a list of numbers from  up to, but not including "stop".
    static List<T> range(T start, T stop, T step = (T) 1) {
        xassert_msg(!Math::isInfinite((double) (stop - start) / step), "Range cannot be infinite.");
        int size = (int) ((stop - start) / step);
        List<T> out;
        out.reserve(size);
        for (T i = start; i < stop; i += step) {
            out.add(i);
        }
        return out;
    }
    static List<T> range(T stop) {
        return range((T)0, stop, (T)1);
    }
    /// Randomly rearrange all elements.
    void shuffle() {
        Algorithm::shuffle(m_elements, count());
    }
    /// Sorts elements in ascending order.
    void sort() {
        Algorithm::sort(m_elements, count());
    }
    /// Like sort, but also preserves the relative order of elements
    /// with equivalent values, at the cost of some performance and
    /// memory usage.
    void stableSort() {
        Algorithm::stableSort(m_elements, count());
    }
    /// A generic iterator function
    template<class AE_CALLBACK>
    void each(AE_CALLBACK callback) {
        for (int i = 0; i < count(); i += 1) {
            callback((*this)[i]);
        }
    }
    template<class AE_CALLBACK>
    void eachi(AE_CALLBACK callback) {
        for (int i = 0; i < count(); i += 1) {
            callback((*this)[i], i);
        }
    }
    /// Creates a new list with all elements that
    /// pass the test implemented by the provided
    /// function.
    template<class AE_CALLBACK>
    List<T> filter(AE_CALLBACK callback) {
        List out;
        for (int i = 0; i < count(); i += 1) {
            const T& element = (*this)[i];
            if (callback(element)) {
                out.add(element);
            }
        }
        return out;
    }
    template<class AE_CALLBACK>
    List<T> filteri(AE_CALLBACK callback) {
        List out;
        for (int i = 0; i < count(); i += 1) {
            const T& element = (*this)[i];
            if (callback(element, i)) {
                out.add(element);
            }
        }
        return out;
    }
    /// Creates a new array with the results of
    /// calling a provided function on every
    /// element in this array.
    template<typename AE_CALLBACK>
    List<T> map(AE_CALLBACK callback) {
        List<T> out;
        for (int i = 0; i < count(); i += 1) {
            const T& element = (*this)[i];
            out.add(callback(element));
        }
        return out;
    }
    template<class TYPE, typename AE_CALLBACK>
    List<TYPE> map(AE_CALLBACK callback) {
        List<TYPE> out;
        for (int i = 0; i < count(); i += 1) {
            const T& element = (*this)[i];
            out.add(callback(element));
        }
        return out;
    }
    template<typename AE_CALLBACK>
    List<T> mapi(AE_CALLBACK callback) {
        List<T> other;
        for (int i = 0; i < count(); i += 1) {
            const T& element = (*this)[i];
            other.add(callback(element, i));
        }
        return other;
    }
    template<class TYPE, typename AE_CALLBACK>
    List<TYPE> mapi(AE_CALLBACK callback) {
        List<TYPE> other;
        for (int i = 0; i < count(); i += 1) {
            const T& element = (*this)[i];
            other.add(callback(element, i));
        }
        return other;
    }
    /// Applies a function against an accumulator and each
    /// value of the array (from left-to-right) to reduce
    /// it to a single value.
    template<class AE_CALLBACK>
    T reduce(AE_CALLBACK callback) {
        T prev = (*this)[0];
        for (int i = 1; i < count(); i += 1) {
            prev = callback(prev, (*this)[i]);
        }
        return prev;
    }
    template<typename PREV, typename AE_CALLBACK>
    PREV& reduce(PREV& initial, AE_CALLBACK callback) {
        PREV& prev = initial;
        for (int i = 0; i < count(); i += 1) {
            prev = callback(prev, (*this)[i]);
        }
        return prev;
    }
    template<typename PREV, typename AE_CALLBACK>
    PREV& reduce(PREV&& initial, AE_CALLBACK callback) {
        PREV& prev = initial;
        for (int i = 0; i < count(); i += 1) {
            prev = callback(prev, (*this)[i]);
        }
        return prev;
    }
    template<class AE_CALLBACK>
    T reducei(AE_CALLBACK callback) {
        T prev = (*this)[0];
        for (int i = 1; i < count(); i += 1) {
            prev = callback(prev, (*this)[i], i);
        }
        return prev;
    }
    template<class TYPE, typename AE_CALLBACK>
    TYPE& reducei(TYPE& initial, AE_CALLBACK callback) {
        TYPE& prev = initial;
        for (int i = 0; i < count(); i += 1) {
            prev = callback(prev, (*this)[i], i);
        }
        return prev;
    }
    template<class TYPE, typename AE_CALLBACK>
    TYPE& reducei(TYPE&& initial, AE_CALLBACK callback) {
        TYPE& prev = initial;
        for (int i = 0; i < count(); i += 1) {
            prev = callback(prev, (*this)[i], i);
        }
        return prev;
    }
    T sum() {
        return reduce([](T prev, T curr) {
            return prev + curr;
        });
    }

private:
    //T m_allocator;
    T* m_elements;
    int m_capacity;
    int m_count;

public:
    /*class Iterator
    {
    public:
        Iterator(List* host, int index)
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
        const T& operator*() const
        {
            return (*m_host)[m_index];
        }
    private:
        List* m_host;
        int m_index;
    };*/
    class Iterator {
    public:
        Iterator(const List* host, int index) {
            m_host = host;
            m_index = index;
        }

        void reset() {
            m_index = 0;
        }

        bool operator!=(const Iterator& other) const {
            return m_index != other.m_index;
        }

        const Iterator& operator++() {
            m_index++;

            return *this;
        }

        const T& operator*() const {
            return (*m_host)[m_index];
        }

    private:
        const List* m_host;
        int m_index;
    };

    Iterator begin() {
        return Iterator(this, 0);
    }

    Iterator end() {
        return Iterator(this, m_count);
    }

    Iterator cbegin() {
        return Iterator(this, 0);
    }

    Iterator cend() {
        return Iterator(this, m_count);
    }
};
}