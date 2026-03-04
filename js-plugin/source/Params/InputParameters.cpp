#include "InputParameters.h"

/*
    Within the Parameter Creating process, we must include STRUCT_NAME.param->init(apvts); to initialize each
    AudioParameterWrapper. This must happen before createParameterGroup for the parameters to work
*/
InputParameters::InputParameters(juce::AudioProcessorValueTreeState& _apvts) : Parameters(_apvts), apvts(_apvts)
{
    inputParams.inGainParam->init(apvts);
    inputParams.panParam->init(apvts);
}

/*
    Creates a group of parameters that can be added to the APVTS layout in the PluginProcessor file.

    Creating the actual parameters that the AudioParameterWrappers encapsulate is being done here.
*/
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

/*
Resets a parameter if it was double-clicked on.
*/
void InputParameters::reset()
{
    inputParams.inGainParam->reset();
    inputParams.panParam->reset();
}

/*
    some juce boilerplate that I forgot what it does
*/
void InputParameters::prepareToPlay(int sampleRate, double duration)
{
    inputParams.inGainParam->prepareToPlay(sampleRate, duration);
    inputParams.panParam->prepareToPlay(sampleRate, duration);

    reset(); // set params to default value
}

/*
    Applies a smoothing function to changing parameter values to
    prevent unwanted noise (especially for changes in gain)
*/
void InputParameters::smoothen()
{
    inputParams.inGainParam->smoothen();
    inputParams.panParam->smoothen();
}

/*
    updates the parameter on value change.
*/
void InputParameters::update()
{
    inputParams.inGainParam->update();
    inputParams.panParam->update();
}