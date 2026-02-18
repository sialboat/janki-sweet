#pragma once

#ifndef GAIN_H
#define GAIN_H

#include <cmath>
#include "Buffer.h"

/*
    gain.h

    contains a basic gain object inspired by juce::dsp::Gain. Comptues the gain on floating point
    samples.
*/

enum class GAIN_TYPE {
    LINEAR, DECIBEL, FUNCTION
};

class gain
{
public:
    gain();
    gain(GAIN_TYPE type, float multiplier);
    gain(GAIN_TYPE type, float multiplier, float ramp);

    float process(float in);                    // applies a gain to the incoming sample based on gain_type, defaults to DECIBEL.

    GAIN_TYPE get_gain_type() { return gain_type; }
    float get_ramp_value() { return ramp_value; }
    float get_multiplier() { return multiplier; }

    void set_multiplier(float mult) { multiplier = mult; }
    void set_gain_type(GAIN_TYPE type) { gain_type = type; }

private: // we don't necessarily need to reveal these to the world
    float process_linear(float in);             // applies a linear-scaling gain to the incoming sample regardless of gain_type
    float process_decibel(float in);            // applies a decibel-scaling gain to the incoming sample regardless of gain_type
    virtual float process_function(float in) = default;     // applies a custom function as gain to the incoming sample.

private:
    GAIN_TYPE gain_type;
    float ramp_value;                   // linearly smooths between gain values via a linear interpolation
    float multiplier
};

#endif