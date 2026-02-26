#pragma once

#ifndef PANNING_H
#define PANNING_H

#include <cmath>
// #include <assert>
#include "Utils/decibel_conversions.h"

#define DEFAULT_MULT 3.0f
#define MULT_4_5 4.5f
#define MULT_6 6.0f

enum class PANNING_RULE
{
    LINEAR, EQUAL_POWER, SQRT
};

// http://gdsp.hf.ntnu.no/lessons/1/5/
// https://www.dsprelated.com/freebooks/sasp/Panning_Problem.html
// we assume the pan values passed into this class is between -1.0f and 1.0f
// WE DO NOT ACTUALLY CHECK THIS IS THE CASE BECAUSE I AM LAZY AND HAVE NOT 
// IMPLEMENTED IT YET.
class panner
{
public:

    panner() : rule(PANNING_RULE::EQUAL_POWER), pan_value(0.0f), mult(1.0f) {}
    panner(PANNING_RULE r, float b) : rule(r), pan_value(0.0f), mult(b) {}
    panner(PANNING_RULE r) : rule(r), pan_value(0.0f), mult(1.0f) {}
    panner(float b) : rule(PANNING_RULE::EQUAL_POWER), pan_value(0.0f), mult(b) {}

    void process(float& left, float& right);                            // given pointers to the left and right channels of audio, apply panning.
    void reset();                                                       // re-initializes the panning processor.

    void set_rule(PANNING_RULE new_rule) {rule = new_rule;}             // sets a new pan processing rule.
    void set_multiplier(float new_mult) { mult = new_mult; }            // sets a new multiplier value
    void set_pan_value(float new_value) { pan_value = new_value; }      // sets a new pan value
    float get_pan_value() { return pan_value; }                         // gets pan value.
    float get_multiplier() { return mult; }                             // gets the multiplier value.
    PANNING_RULE get_rule() { return rule; }                            // gets the panning rule.
    
private:
    void pan_linear(float& left, float& right);              // linear panning processing
    void pan_equal_power(float& left, float& right);         // equal power panning 
    void pan_sqrt(float& left, float& right);                // sqaure root panning

    
    PANNING_RULE rule;                                                  // panning rule to which the object will process
    float pan_value;                                                    // internal pan value
    float mult;                                                         // decibel multiplier value that compensates for perceptual losses. 
                                                                        // CONVERT TO DB BY USING convert_db_to_gain() FUNCTION to conver it
                                                                        // to a linear multiplier
};

#endif