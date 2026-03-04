#pragma once

#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

// #include <JuceHeader.h>

// include the actual module headers that we are using so 
// CMake does not scream at us
#include <juce_audio_processors/juce_audio_processors.h>

/*
    AudioDevice

    Virtual class used to abstract DSP classes to a prepare and process
    method. The prepare method should ideally reset values and zero buffers 
    while the process method should iterate sample by sample / channel by 
    channel to apply DSP to a juce::AudioBuffer<float> object. That way,
    all that is needed to do at the PluginProcessor's processBlock()
    function is to update parameters and process changes. 
*/
class AudioDevice
{
    public:
    virtual void prepare(double s, int i) = 0;
    virtual void process(juce::AudioBuffer<float>& b) = 0;
    virtual ~AudioDevice() = default;
};

#endif