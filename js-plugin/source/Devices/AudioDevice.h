#pragma once

#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

// #include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>


class AudioDevice
{
    public:
    virtual void prepare(double s, int i) = 0;
    virtual void process(juce::AudioBuffer<float>& b) = 0;
    // virtual ~AudioDevice() = default;
};

#endif