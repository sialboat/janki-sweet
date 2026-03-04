// InputProcessor.h
#pragma once

#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

// #include <JuceHeader.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include "AudioDevice.h"
#include "Utils/Measurement.h"
#include "Params/InputParameters.h"
#include "le-janky/gain.h"
#include "le-janky/panning.h"

#define INPUT_INDEX 0
#define OUTPUT_INDEX 1

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
    InputProcessor(InputParameters& ip);
    //feed pan parameter into panner
    void setInputGainLinear(float g) {inputGainLinear = g;}
    void setInputPan (float p) {inputPan = p;}

    void prepare(double sampleRate, int samplesPerBlockExpected) override;
    void process(juce::AudioBuffer<float>& in) override;

    // Adding this so we can access input measurement levels
    Measurement& left() noexcept { return levelL; }
    Measurement& right() noexcept { return levelR; }

    private:
    // we don't rlly need these because the parameters are stored in the AudioParameters
    // encapsulated by the AudioParameterWrapper. The updates will be called by an update()
    // function in the main AudioProcessor i think
    float inputGainLinear = 1.0f; //already linear
    float inputPan = 0.0f; //[-1,1] smoothed
    gain gainEffect;
    panner panEffect;
    Measurement levelL, levelR;
};

#endif