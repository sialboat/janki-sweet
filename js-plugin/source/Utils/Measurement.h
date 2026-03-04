#pragma once

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <atomic>

// structs and objects are effectively the same thing but structs have all functions public
struct Measurement 
{
    void reset() noexcept
    {
        value.store(0.0f);
    }

    void updateIfGreater(float newValue) noexcept
    {
        auto oldValue = value.load();
        while(newValue > oldValue && !value.compare_exchange_weak(oldValue, newValue));
    }

    // noexcept so the compiler does not cry
    float readAndReset() const noexcept
    {
        return value.exchange(0.0f);
    }

    // mutable exists so we can let non static variables inside of a const function
    mutable std::atomic<float> value; 
};

#endif