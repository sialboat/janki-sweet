#include "InputParameters.h"

InputParameters::InputParameters(juce::AudioProcessorValueTreeState& _apvts) : Parameters(_apvts), apvts(_apvts)
{
    inputParams.inGainParam->init(apvts);
    inputParams.panParam->init(apvts);
}

// add parameters here
std::unique_ptr<PARAMS> InputParameters::createParameterGroup()
{
    // std::unique_ptr<juce::AudioProcessorParameterGroup> group;
    auto inputParams = std::make_unique<INPUT_PARAMS>();

    inputParams->group = std::make_unique<juce::AudioProcessorParameterGroup>("in_params", "Input", "|");

    inputParams->inGainParam = FloatGainParamWrapper::create(
        *inputParams->group, juce::ParameterID{"inputGain", 1}, juce::String{"Input Gain"},
        juce::NormalisableRange<float>{-24.0f, 24.0f}, 0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)
    );
    inputParams->panParam = FloatParamWrapper::create(
        *inputParams->group, juce::ParameterID{"inputPan", 1}, juce::String{"Input Pan"},
        juce::NormalisableRange<float>{-1.0f, 1.0f, 0.01f}, 0.0f, 
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPan)
    );

    return inputParams;
}

void InputParameters::prepareToPlay(int sampleRate, double duration)
{
    inputParams.inGainParam->prepareToPlay(sampleRate, duration);
    inputParams.panParam->prepareToPlay(sampleRate, duration);
}

void InputParameters::reset()
{
    inputParams.inGainParam->reset();
    inputParams.panParam->reset();
}

void InputParameters::smoothen()
{
    inputParams.inGainParam->smoothen();
    inputParams.panParam->smoothen();
}

void InputParameters::update()
{
    inputParams.inGainParam->update();
    inputParams.panParam->smoothen();
}