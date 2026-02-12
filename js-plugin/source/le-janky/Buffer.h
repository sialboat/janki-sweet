
#pragma once

#ifndef BUFFER_H
#define BUFFER_H

/* 
    Base buffer class that potentially hopefully transfers
    well across other DSP primitives
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