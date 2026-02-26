#pragma once

#ifndef INPUT_PARAMETERS_H
#define INPUT_PARAMETERS_H

#include <juce_audio_processors/juce_audio_processors.h>
#include "ParameterWrapper.h"
#include "Parameters.h"

// add parameters here
struct INPUT_PARAMS : public PARAMS {
    std::unique_ptr<FloatGainParamWrapper> inGainParam;
    std::unique_ptr<FloatParamWrapper> panParam;
};

class InputParameters : public Parameters
{
    public:

    InputParameters(juce::AudioProcessorValueTreeState& apvts);
    
    static std::unique_ptr<PARAMS> createParameterGroup();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate = 0.05) override;
    void reset() override;
    void update() override;
    void smoothen() override;

    INPUT_PARAMS& getInputParams() { return inputParams; }

    private:

    INPUT_PARAMS inputParams;
    
    juce::AudioProcessorValueTreeState& apvts;

    // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InputParameters)
};

#endif