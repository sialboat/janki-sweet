//Parameters.h
#pragma once
#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <juce_audio_processors/juce_audio_processors.h>

/*
    Parameters.h

    Base class that abstracts the basic parameter manager class. JUCE stores all parameters in
    an AudioProcessorValueTreeState data structure, which is used in conjunction with the 
    ParameterWrappers within this object to efficiently manage numerous parameters.
*/


class base_param
{
    public:
    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate = 0.05) = 0;
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual void smoothen() = 0;
};

typedef struct PARAMS {
    std::unique_ptr<juce::AudioProcessorParameterGroup> group;
    // parameters and group go here

    ~PARAMS() = default;
} PARAMS;

class Parameters : public base_param
{
    public:
    // virtual std::unique_ptr<PARAMS> createParameterGroup() = 0;

    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate = 0.05) override = 0;
    virtual void reset() override = 0;
    virtual void update() override = 0;
    virtual void smoothen() override = 0;

    Parameters(juce::AudioProcessorValueTreeState& apvts) {}
    Parameters();
    virtual ~Parameters() = default;
};


//converts a parameter time value into text, storing it in a juce::String object and returning it
//to the caller.
static juce::String stringFromMilliseconds(float value, int)
{
    if (value < 10.0f) {
        return juce::String(value, 2) + " ms";
    } else if (value < 100.0f) {
        return juce::String(value, 1) + " ms";
    } else if (value < 1000.0f) {
        return juce::String(int(value)) + " ms";
    } else {
        return juce::String(value * 0.001f, 2) + " s";
    }
}

static juce::String stringFromDecibels(float value, int)
{
    return juce::String(value, 1) + " dB";
}

static juce::String stringFromSemitones(float value, int)
{
    return juce::String(value, 1) + " st";
}

static juce::String stringFromPercent(float value, int)
{
    return juce::String(int(value)) + " %";
}

static juce::String stringFromPan(float value, int)
{
    // Convert to percentage
    float leftPercentage = (1.0f + value) / 2.0f * 100.0f;  
    float rightPercentage = (1.0f - value) / 2.0f * 100.0f;

    return juce::String(leftPercentage, 1) + "% L / " + 
        juce::String(rightPercentage, 1) + "% R";
}

// static juce::String stringFromPercentOddEven(float value, int)
// {
//     //at 0 (12:00), 50% odd, 50% even
//     //at -100, we have 100% odd, 0% even
//     //at 100, we have 0% odd, 100% even
//     //value > 0, more even
//     float odd = 100.0f - value;
//     float even = value;
    
//     return juce::String((int) odd) + " / " + juce::String((int) even) + " %";
    
// }
// static juce::String stringFromPercentTapeTube(float value, int)
// {
//     //at value == 100, we have 0/100
//     //at value == 0, we have 100/0
//     float tape = 100.0f - value;
//     float tube = value;
    
//     return juce::String((int) tape) + " / " + juce::String((int) tube) + " %";
// }

static juce::String stringFromPercentFloat(float value, int)
{
    return juce::String(value, 2) + " %";
}

// //converts milliseconds float value to a juce::String value
// static float millisecondsFromString(const juce::String& text)
// {
//     float value = text.getFloatValue();
//     if(!text.endsWithIgnoreCase("ms")) {
//         if(text.endsWithIgnoreCase("s") || value < Parameters::minDelayTime) {
//             return value * 1000.0f;
//         }
//     }
//     return value;
// }

static juce::String stringFromHz(float value, int)
{
    if(value < 1000.0f) {
        return juce::String(int(value)) + "Hz";
    } else if (value < 10000.0f) {
        return juce::String(value / 1000.0f, 2) + " kHz";
    } else {
        return juce::String(value / 1000.0f, 1) + " kHz";
    }
}
static float hzFromString(const juce::String& str)
{
    float value = str.getFloatValue();
    if(value < 20.0f) {
        return value * 1000.0f;
    }
    return value;
}

#endif