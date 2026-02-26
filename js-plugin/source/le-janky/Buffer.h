
#pragma once

#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <cstddef>
#include <algorithm>

/* 
    Base buffer class that potentially hopefully transfers
    well across other DSP primitives

    Some things I learned about writing this class:
    - the explicit keyword tells C++ that this is the constructor that it
      must use when creating a buffer object. 
    - T& operator[] allows you to rewrite the behavior of the arr[i] operation.
        - you can do this with other operators as well (<, >, <=, >=, ++, +=, etc.)
*/
template <typename TYPE>
class buffer
{
    public:
    explicit buffer(size_t size) : capacity(size), arr(std::make_unique<TYPE[]>(capacity)) {}

    // Operators to modify the index of the the data array. Two exist so we can accomodate for
    // Const and non-const objects.
    TYPE& operator[](size_t i) { return arr[i]; }
    const TYPE& operator[](size_t i) const { return arr[i]; }

    void clear() { std::fill_n(arr.get(), capacity, TYPE{}); }
    size_t size() { return capacity; }
    TYPE* data() { return arr.data(); }        // return a raw pointer

    void resize(size_t newSize) {
        std::unique_ptr<TYPE[]> copy_to = std::make_unique<TYPE[]>(newSize);

        for(size_t i = 0; i < newSize; i++) {
            copy_to[i] = arr[i];
            if(i > newSize)
                copy_to[i] = TYPE{};
        }

        // std::copy(arr.get(), newSize, copy_to);

        arr = std::move(copy_to);
        capacity = newSize;
    }

    private:
    size_t capacity;
    std::unique_ptr<TYPE[]> arr;

};

// template<typename CHANNELS, typename TYPE>
// class buffers_plural
// {
//     public:
//     explicit buffer(size_t size) : capacity(size), arr(std::make_unqiue<TYPE[CHANNELS][]>(capacity)) {}

//     TYPE& operator[][](size_t i) { return arr[i]; }
// };

#endif