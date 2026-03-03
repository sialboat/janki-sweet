#include "clipper.h"

float clipper::process(float in)
{
    switch(rule)
    {
        case CLIP_MODES::OFF: return in;
        case CLIP_MODES::SOFT: return process_soft(in);
        case CLIP_MODES::HARD: return process_hard(in);
        default: return in;
    }
    return in; // we shouldn't get here
}

void clipper::reset()
{
    rule = CLIP_MODES::SOFT;
}

float clipper::process_soft(float in)
{
    return (in >= 1.0f) ? std::tanh(2.40f * in) : in;
}

float clipper::process_hard(float in)
{
    return (in >= 1.0f) ? 1.0f : in;
}

float clipper::process_threshold(float in, float thresh, float clamp)
{
    return (in >= thresh) ? ( (clamp <= 1.0f && clamp > 0.0f) ? clamp : 1.0f ) : in;
}
