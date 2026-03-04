// OutputParameters.h
#pragma once

#ifndef OUTPUT_PARAMETERS_H
#define OUTPUT_PARAMETERS_H 

#include <juce_audio_processors/juce_audio_processors.h>
#include "ParameterWrapper.h"
#include "Parameters.h"
#include <cmath>            // I think this is needed for std::max

// namespace PARAM_ID
// {
//     const juce::ParameterID outputGainParamID {"outputGain", 1};
//     const juce::ParameterID outputPanParamID {"outputPan", 1};
//     const juce::ParameterID outputMixParamID {"outputMix", 1};
//     const juce::ParameterID clipModeParamID {"clipMode", 1};
// };

//output parameters
struct OUTPUT_PARAMS : public PARAMS{
    std::unique_ptr<BoolParamWrapper> bypassParam;
    std::unique_ptr<FloatParamWrapper> outputPan; // [-1, 1]
    std::unique_ptr<FloatGainParamWrapper> outGainParam;
    std::unique_ptr<FloatParamWrapper> mixParam; //0-100%
    std::unique_ptr<ChoiceParamWrapper> clipModeParam; //off/hard/soft
};

/*
    Output Parameters

    Parameter class that manages parameter values (between GUI and AudioProcessor)
    for the Output-related parameters and DSP effects (Input Gain and Pan and Clipping).
*/
class OutputParameters : public Parameters {
    public:
        OutputParameters(juce::AudioProcessorValueTreeState& apvts);

        static std::unique_ptr<PARAMS> createParameterGroup();

        void prepareToPlay(int samplesPerBlockExpected, double sampleRate = 0.05) override;
        void reset() override;
        void update() override;
        void smoothen() override;

        OUTPUT_PARAMS& getOutputParams() {return outputParams;}
        const juce::StringArray& getClipperModes() const noexcept { return clipperModes; }
    private:
        OUTPUT_PARAMS outputParams;
        static inline juce::StringArray clipperModes = {"Off", "Hard", "Soft"};
        juce::AudioProcessorValueTreeState& apvts;
};

#endif