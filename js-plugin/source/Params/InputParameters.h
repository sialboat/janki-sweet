#pragma once

#ifndef INPUT_PARAMETERS_H
#define INPUT_PARAMETERS_H

#include <juce_audio_processors/juce_audio_processors.h>
#include "ParameterWrapper.h"
#include "Parameters.h"

/*
    PARAMS struct that contains static references to all 
    AudioParameterWrappers used within this parameters class.

    I think this the way we must do this because the 
    createParameterGroup() function that exists here is required
    to be static so the arguments that which we pass through it must also
    be static?
*/

// add parameters here
struct INPUT_PARAMS : public PARAMS {
    std::unique_ptr<FloatGainParamWrapper> inGainParam;
    std::unique_ptr<FloatParamWrapper> panParam;
};

/*
    InputParameters

    Parameter class that manages parameter values (between GUI and AudioProcessor)
    for the Input-related parameters and DSP effects (Input Gain and Pan).
*/
class InputParameters : public Parameters
{
    public:

    // InputParameters();
    InputParameters(juce::AudioProcessorValueTreeState& apvts);
    
    static std::unique_ptr<PARAMS> createParameterGroup();
    
    // Boilerplate JUCE function for something I don't remember off the top of my head
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate = 0.05) override;

    // Resets the parameter to the default value (upon double-clicking)
    void reset() override;

    // How to change parameters upon updating them
    void update() override;

    // Whether or not we should be applying a smoothing function to changing values
    void smoothen() override;

    INPUT_PARAMS& getInputParams() { return inputParams; }

    private:

    INPUT_PARAMS inputParams;
    
    juce::AudioProcessorValueTreeState& apvts;

    // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputParameters)
};

#endif