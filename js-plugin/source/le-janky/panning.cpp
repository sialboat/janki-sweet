#include "panning.h"

void panner::process(float& left, float& right)
{
    switch(rule)
    {
        case PANNING_RULE::LINEAR:          
            pan_linear(left, right); 
            break;
        case PANNING_RULE::EQUAL_POWER:     
            pan_equal_power(left, right);
            break;
        case PANNING_RULE::SQRT:            
            pan_sqrt(left, right);
            break;
        default: 
            pan_equal_power(left, right);
            break;
    }
}

void panner::reset()
{
    mult = DEFAULT_MULT;
    rule = PANNING_RULE::EQUAL_POWER;
}

void panner::pan_linear(float& left, float& right)
{
    // assert(pan_value <= 1.0f && pan_value >= 0.0f);
    left *= ((1.0f - pan_value) / 2.0f) * convert_db_to_gain(mult, DEFAULT_MINUS_INF);
    right *= (1.0f + pan_value) / 2.0f * convert_db_to_gain(mult, DEFAULT_MINUS_INF);
}

void panner::pan_equal_power(float& left, float& right)
{
    float angle = 0.7853981633974483f * (pan_value + 1.0f);
    left *= std::sin(angle) * convert_db_to_gain(mult, DEFAULT_MINUS_INF);
    right *= std::cos(angle) * convert_db_to_gain(mult, DEFAULT_MINUS_INF);
}

void panner::pan_sqrt(float& left, float& right)
{
    left *= std::sqrt((1.0f - pan_value) / 2.0f) * convert_db_to_gain(mult, DEFAULT_MINUS_INF);
    right *= std::sqrt((1.0f + pan_value) / 2.0f) * convert_db_to_gain(mult, DEFAULT_MINUS_INF);
}

