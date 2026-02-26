#pragma once

#ifndef GAIN_H
#define GAIN_H

#include <cmath>
#include "Buffer.h"

#define DEFAULT_BITRATE 24

/*
    gain.h

    contains a basic gain object inspired by juce::dsp::Gain. Comptues the gain on floating point
    samples.
*/

enum class GAIN_TYPE {
    LINEAR, DB_SPL, DB_FS, FUNCTION
};

class gain
{
public:
    gain();
    gain(GAIN_TYPE type, float multiplier);
    gain(GAIN_TYPE type, float multiplier, float ramp);

    float process(float in);                    // applies a gain to the incoming sample based on gain_type, defaults to DECIBEL.
    void reset();                               // initializes to the factory default values

    GAIN_TYPE get_gain_type() { return gain_type; }
    float get_ramp_value() { return ramp_value; }
    float get_multiplier() { return multiplier; }
    uint8_t get_bitrate() { return bitrate; }

    // getters for multiplier values in dbSPL, dbFS
    // float get_dbfs_value() { return  }

    void set_ramp_value(float n) { ramp_value = n; }
    void set_multiplier(float mult) { multiplier = mult; }
    void set_gain_type(GAIN_TYPE type) { gain_type = type; }
    void set_bitrate(uint8_t n) { bitrate = n; }

private: // we don't necessarily need to reveal these to the world
    float process_linear(float in);             // applies a linear-scaling gain to the incoming sample regardless of gain_type
    float process_dbspl(float in);              // applies a decibel-scaling gain (dbSPL) to the incoming sample regardless of gain_type
    float process_dbfs(float in);               // applies a decibel-scaling gain (dbFS) to the incoming sample regardless of gain_type
    float process_dbfs_gain(float in);          // applies a decibel-scaling gain (dbFS), does not account for bitrate.
    float lerp_gain_value();                    // linearly interpolates to the next gain value so we don't 
    virtual float process_function(float in);   // applies a custom function as gain to the incoming sample.

private:
    GAIN_TYPE gain_type;                // enum state that determines the function that will determine the gain
    float ramp_value;                   // linearly smooths between gain values, represents num. of samples to interpolate over
    float multiplier;                   // target multiplier that we set
    float current_multiplier;           // current multiplier value that is being linearly interpolated.
    uint8_t bitrate;                    // bitrate of audio file
};

#endif