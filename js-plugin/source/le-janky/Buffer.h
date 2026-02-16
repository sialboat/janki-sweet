
#pragma once

#ifndef BUFFER_H
#define BUFFER_H

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
    explicit buffer(size_t size) : capacity(size), data(std::make_unique<TYPE[]>(capacity)) {}

    // Operators to modify the index of the the data array. Two exist so we can accomodate for
    // Const and non-const objects.
    TYPE& operator[](size_t i) { return data[i]; }
    const TYPE& operator[](size_t i) const { return data[i]; }

    void clear() { std::fill_n(data.get(), capacity, TYPE{}); }
    size_t size() { return capacity; }
    TYPE* data() { return data.data(); }        // return a raw pointer

    void resize(size_t newSize) {
        std::unique_ptr<TYPE[]> copy_to = std::make_unique<TYPE[]>(newSize);

        std::copy(data.get(), newSize, copy_to);

        data = std::move(copy_to);
        capacity = newSize;
    }

    private:
    std::unique_ptr<TYPE[]> data;
    size_t capacity;

};

#endif