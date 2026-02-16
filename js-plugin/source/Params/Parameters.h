
#pragma once
#ifndef PARAMETERS_H
#define PARAMETERS_H

/*
    Parameters.h

    Base class that abstracts the basic parameter manager class. JUCE stores all parameters in
    an AudioProcessorValueTreeState data structure, which is used in conjunction with the 
    ParameterWrappers within this object to efficiently manage numerous parameters.
    Each APVTS (and by extension the base parameter object) contains all parameters required
    for each part of the effect (the input section, an effect module, the output effect, etc.).
*/

#include <JuceHeader.h>

class Parameters
{
public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);

    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) noexcept;
    virtual void reset() noexcept;
    virtual void update() noexcept;
    virtual void smoothen() noexcept;
}

#endif