#include "gain.h"

gain::gain() : gain_type(GAIN_TYPE::DECIBEL), ramp_value(100.0f), 
    multiplier(1.0f);

gain::gain(GAIN_TYPE type, float multiplier) : gain_type(type), 
    ramp_value(100.0f), multiplier(1.0f) {}

gain::gain(GAIN_TYPE type, float multiplier, float ramp) : gain_type(type),
    ramp_value(ramp), multiplier(multiplier) {} 

float gain::process(float input)
{
    switch(gain_type)
    {
        case GAIN_TYPE::LINEAR: return process_linear(input);
        case GAIN_TYPE::DECIBEL: return process_decibel(input);
        case GAIN_TYPE::FUNCTION: return process_function(input);
        default: return process_decibel(input);
    }
}

float gain::process_linear(float in)
{
    return in * multiplier;
}

float gain::process_decibel(float in)
{
    // apply log change of base because std::log is the natural log
    return multiplier * 20 * (std::log(in / 2e-5) / std::log(10));
}

virtual float gain::process_function(float in)
{
    return process_decibel(in);
}