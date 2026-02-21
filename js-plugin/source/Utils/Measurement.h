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

    float readAndReset()
    {
        return value.exchange(0.0f);
    }

    std::atomic<float> value;
};

#endif