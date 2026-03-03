// InputProcessor.h
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
    //feed pan parameter into panner
    void setInputGainLinear(float g) {inputGainLinear = g;}
    void setInputPan (float p) {inputPan = p;}

    void prepare(double sampleRate, int samplesPerBlockExpected) override;
    void process(juce::AudioBuffer<float>& in) override;

    private:
    // we don't rlly need these because the parameters are stored in the AudioParameters
    // encapsulated by the AudioParameterWrapper. The updates will be called by an update()
    // function in the main AudioProcessor i think
    float inputGainLinear = 1.0f; //already linear
    float inputPan = 0.0f; //[-1,1] smoothed
    gain gainEffect;
    panner panEffect;
};

#endif