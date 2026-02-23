#include "gain.h"

gain::gain() : gain_type(GAIN_TYPE::DB_FS), ramp_value(100.0f), 
    multiplier(1.0f), bitrate(DEFAULT_BITRATE) {}

gain::gain(GAIN_TYPE type, float multiplier) : gain_type(type), 
    ramp_value(100.0f), multiplier(1.0f), bitrate(DEFAULT_BITRATE) {}

gain::gain(GAIN_TYPE type, float multiplier, float ramp) : gain_type(type),
    ramp_value(ramp), multiplier(multiplier), bitrate(DEFAULT_BITRATE) {} 

float gain::process(float input)
{
    switch(gain_type)
    {
        case GAIN_TYPE::LINEAR: return process_linear(input);
        case GAIN_TYPE::DB_SPL: return process_dbspl(input);
        case GAIN_TYPE::DB_FS: return process_dbfs(input);
        case GAIN_TYPE::FUNCTION: return process_function(input);
        default: return process_dbfs(input);
    }
}

float gain::process_linear(float in)
{
    // this exists to prevent zipper noise / clicks if we have large changes in gain values
    if(current_multiplier != multiplier)
        current_multiplier += lerp_gain_value();
    return in * current_multiplier;
}

float gain::process_dbspl(float in)
{
    // this exists to prevent zipper noise / clicks if we have large changes in gain values
    if(current_multiplier != multiplier)
        current_multiplier += lerp_gain_value();
    // apply log change of base because std::log is the natural log
    return current_multiplier  * 20 * std::log10(in) - std::log10(2e-5);
    // return current_multiplier * 20 * (std::log(in / 2e-5) / std::log(10));
}

// this one is commonly used in DAWs and audio software as the reference floor is based off of
// half of the maximum capacity of the data type.
float gain::process_dbfs(float in)
{
    if(current_multiplier != multiplier)
        current_multiplier += lerp_gain_value();
    return current_multiplier * 20 * std::log10(std::abs(in)) - std::log10(std::pow(2, bitrate - 1));
    // return current_multiplier * 20 * std::log(std::abs(in)) / (/* 2^(bitrate - 1) */ ) / std::log(10);  
}

/*
    Linearly interpolates between the current gain multiplier by returning the delta between
    the target multiplier and current multiplier based on the target multiplier value and the 
    ramp duration through
    (current_mult - target_mult) / (ramp_value)
*/
float gain::lerp_gain_value()
{
    return (multiplier - current_multiplier) / (ramp_value);
}

/*
    Virtual functions with an implementation exist so a fallback can be put in place
    if the user does not want to implement their own custom function. But if they
    want to define their gain value by some means, they have the ability to override
    this function freely. 
*/
float gain::process_function(float in)
{
    return process_dbfs(in);
}