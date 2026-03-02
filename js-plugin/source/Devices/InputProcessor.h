#pragma once

#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

// #include <JuceHeader.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "AudioDevice.h"
#include "Params/InputParameters.h"
#include "le-janky/gain.h"
#include "le-janky/panning.h"

/*
    InputProcessor

    Class that abstracts the DSP processes needed within the input
    section of the plugin into prepare and process subroutines. 
    More methods can be added to allow access for DSP primitive
    functions.
*/
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