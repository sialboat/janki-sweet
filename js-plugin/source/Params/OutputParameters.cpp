// OutputParameters.cpp
#include "OutputParameters.h"

OutputParameters::OutputParameters(juce::AudioProcessorValueTreeState& _apvts) : Parameters(_apvts), apvts(_apvts)
{
    //outputParams.* pointers are null until createParameterGroup() makes them so it should only be called after
    //apvts has been constructed

    outputParams.outGainParam->init(apvts);
    outputParams.mixParam->init(apvts);
    outputParams.clipModeParam->init(apvts);
    outputParams.outputPan->init(apvts);
    outputParams.bypassParam->init(apvts);
}

std::unique_ptr<PARAMS> OutputParameters::createParameterGroup()
{
    auto outputParams = std::make_unique<OUTPUT_PARAMS>();

    outputParams->group = std::make_unique<juce::AudioProcessorParameterGroup>("out_params", "Output", "|");

    // Output Gain (dB)
    outputParams->outGainParam = FloatGainParamWrapper::create(
        *outputParams->group,
        juce::ParameterID{"outputGain", 1},
        juce::String{"Output Gain"},
        juce::NormalisableRange<float>{-24.0f, 24.0f},
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)
    );

    // Output Mix (0..100%)
    outputParams->mixParam = FloatParamWrapper::create(
        *outputParams->group,
        juce::ParameterID{"outputMix", 1},
        juce::String{"Mix"},
        juce::NormalisableRange<float>{0.0f, 100.0f, 0.1f},
        100.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercentFloat)
    );

    // Clipper Mode
    outputParams->clipModeParam = ChoiceParamWrapper::create(
        *outputParams->group,
        juce::ParameterID{"clipMode", 1},
        juce::String{"Clipper"},
        clipperModes,
        0
    );

    outputParams-> outputPan = FloatParamWrapper::create(
        *outputParams->group, 
        juce::ParameterID{"outputPan", 1}, 
        juce::String{"Pan"},
        juce::NormalisableRange<float>{-1.0f, 1.0f, 0.1f}, 
        0.0f, 
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPan)
    );

    outputParams->bypassParam = BoolParamWrapper::create(
        *outputParams->group, juce::ParameterID{"bypass", 1},
        juce::String{"Bypass"}, false
    );

    return outputParams;
}

void OutputParameters::prepareToPlay(int sampleRate, double duration)
{
    outputParams.outGainParam->prepareToPlay(sampleRate, duration);
    outputParams.mixParam->prepareToPlay(sampleRate, duration);
    outputParams.clipModeParam->prepareToPlay(sampleRate, duration);
    outputParams.outputPan->prepareToPlay(sampleRate, duration);
    // we don't need to prepare the buttons I think

    reset(); // set params to a default value
}

void OutputParameters::reset()
{
    outputParams.outGainParam->reset();
    outputParams.mixParam->reset();
    outputParams.outputPan->reset();
    // outputParams.clipModeParam->reset();
}

void OutputParameters::update()
{
    outputParams.outGainParam->update();
    outputParams.mixParam->update();
    outputParams.clipModeParam->update();

    // since these two are represented by buttons we don't need
    // a reset or smoothen or preparetoplay because there is nothing
    // to prepare here when values are "discrete" (i think)
    outputParams.bypassParam->update();
    outputParams.outputPan->update();
}

void OutputParameters::smoothen()
{
    outputParams.outGainParam->smoothen();
    outputParams.mixParam->smoothen();
    outputParams.outputPan->smoothen();
    // outputParams.clipModeParam->smoothen();
}