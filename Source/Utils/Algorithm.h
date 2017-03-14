#pragma once

#include "Random.h"

#include <algorithm>
#include <utility>

namespace ae {
/// Facilitates algorithms, such as sorting.
class Algorithm {
public:
    /// Randomly rearranges the first "count" elements.
    template<class T>
    static void shuffle(T* elements, int count);
    /// Sorts the first elements "count" elements in ascending order.
    template<class T>
    static void sort(T* elements, int count);
    /// Like sort, but also preserves the relative order of elements
    /// with equivalent values, at the cost of some performance and
    /// memory usage.
    template<class T>
    static void stableSort(T* elements, int count);
    /// Exchanges the values of the arguments.
    template<class T>
    static void swap(T& left, T& right);
    /// Variadic template which returns the maximum value among the
    /// specified arguments.
    template<class T>
    static T max(const T& value);
    template<class T, typename... Args>
    static T max(const T& value, Args... args);
    /// Variadic template which returns true if the specified value
    /// matches any of the other arguments.
    template<class T, class U>
    static bool any(const T& value, const U& arg);
    template<class T, class U, class... Args>
    static bool any(const T& value, const U& arg, Args... args);
};

template<class T>
void Algorithm::shuffle(T* elements, int count) {
    for (int i = 0; i < count; i++) {
        int rand = Random::next(count);
        std::swap<T>(elements[i], elements[rand]);
    }
}

template<class T>
void Algorithm::sort(T* elements, int count) {
    std::sort(elements, elements + count);
}

template<class T>
void Algorithm::stableSort(T* elements, int count) {
    std::stable_sort<T>(elements, elements + count);
}

template<class T>
void Algorithm::swap(T& left, T& right) {
    return std::swap(left, right);
}

template<class T>
T Algorithm::max(const T& value) {
    return value;
}

template<class T, typename... Args>
T Algorithm::max(const T& value, Args... args) {
    return std::max<T>(max(args...), value);
}

template<class T, class U>
bool Algorithm::any(const T& value, const U& arg) {
    return value == arg;
}

template<class T, class U, class... Args>
bool Algorithm::any(const T& value, const U& arg, Args... args) {
    return value == arg || any(value, args...);
}
}