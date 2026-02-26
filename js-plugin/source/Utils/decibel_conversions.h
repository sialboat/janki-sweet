#pragma once

#ifndef DECIBEL_CONVERSIONS_H
#define DECIBEL_CONVERSIONS_H

#define DEFAULT_MINUS_INF -100.0f

/*
    decibel_conversions.h

    dBFS conversions that translate a gain multiplier value to a decibel value (and the other way around)
    because I wanted to write my own. You don't have to use these, this was an exercise / something I wanted
    to do. Using these inline functions may prove to be easier / more lightweight in gain-related computations
    than initializing a le-janky/gain processor.
*/
static inline float convert_db_to_gain(float db, float minus_inf)
{
    return db > minus_inf ? std::pow(db * 0.05f, 10.0f) : minus_inf; 
}

static inline float convert_gain_to_db(float gain, float minus_inf)
{
    return std::max(20.0f * std::log10(gain), minus_inf);
}

#endif