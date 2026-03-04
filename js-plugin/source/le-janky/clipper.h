#pragma once

#ifndef CLIPPER_H
#define CLIPPER_H

#include <cmath>

enum class CLIP_MODES
{
    OFF, SOFT, HARD
};

/*
    clipper class

    basic clipper processor that clamps audio to a certain value if it exceeds a value.
    Soft clip and hard clip algorithms are implemented.
*/
class clipper
{
    public:
    clipper() : rule(CLIP_MODES::SOFT) {}
    clipper(CLIP_MODES mode) : rule(mode) {}

    void reset();                                                   // initializes CLIP_MODES rule to soft clip
    float process(float in);                                        // processes the incoming sample based on the clipping rule

    void set_mode(CLIP_MODES mode) { rule = mode; }
    CLIP_MODES get_mode() { return rule; }

    private:
    float process_soft(float in);                                   // applies a tanh(in) function to the audio if audio >= 1.0f
    float process_hard(float in);                                   // clamps audio at 1.0f if audio >= 1.0f
    float process_threshold(float in, float thresh, float clamp);   // sets audio to clamp if audio >= thresh.

    CLIP_MODES rule;
};

#endif