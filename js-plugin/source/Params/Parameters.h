
#pragma once
#ifndef PARAMETERS_H
#define PARAMETERS_H

// base parameter manager class

#include <JuceHeader.h>

class Parameters
{
public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);

    virtual void prepareToPlay(double sampleRate) noexcept;
    virtual void reset() noexcept;
    virtual void update() noexcept;
    virtual void smoothen() noexcept;
}

#endif