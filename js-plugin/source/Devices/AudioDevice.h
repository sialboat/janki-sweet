#pragma once

#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/buffers/juce_AudioSampleBuffer.h>


class AudioDevice
{
    virtual void prepare(double s, int i);
    virtual void process(juce::AudioBuffer<float>& b);
};

#endif