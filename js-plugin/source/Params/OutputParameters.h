// OutputParameters.h
#pragma once

#ifndef OUTPUT_PARAMETERS_H
#define OUTPUT_PARAMETERS_H 

#include <juce_audio_processors/juce_audio_processors.h>
#include "ParameterWrapper.h"
#include "Parameters.h"

//output parameters
struct OUTPUT_PARAMS : public PARAMS{
    std::unique_ptr<FloatGainParamWrapper> outGainParam;
    std::unique_pts<FloatParamWrapper> mixParam; //o-100%
    std::unique_pts<ChoiceParamWrapper> clipModeParam; //off/hard/soft
}

class OutputParameters : public Parameters{
    public:
        OutputParameters(juce::AudioProcessorValueTreeState& apvts);

        static std::unique_pts<PARAMS> createParameterGroup();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate = 0.05) override;
        void reset() override;
        void update() override;
        void smoothen() override;

        OUTPUT_PARAMS& getOutputParams() {return outputParams;}
    private:
        OUTPUT_PARAMS outputParams;
        juce::StringArray clipperModes = {"Off", "Hard", "Soft"};
        juce::AudioProcessorValueTreeState& apvts;
};

#endif