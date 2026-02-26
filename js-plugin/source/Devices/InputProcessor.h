#pragma once

#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

// #include <JuceHeader.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "AudioDevice.h"
#include "Params/InputParameters.h"
#include "le-janky/gain.h"
#include "le-janky/panning.h"

class InputProcessor : public AudioDevice
{
    public:
    InputProcessor();

    void prepare(double sampleRate, int samplesPerBlockExpected) override;
    void process(juce::AudioBuffer<float>& in) override;

    private:
    gain gainEffect;
    panner panEffect;
};

#endif