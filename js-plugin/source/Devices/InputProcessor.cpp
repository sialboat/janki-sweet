// InputProcessor.cpp
#include "InputProcessor.h"

InputProcessor::InputProcessor() : gainEffect(), panEffect()
{}

void InputProcessor::prepare(double sampleRate, int samplePerBlockExpected)
{
    juce::ignoreUnused(sampleRate, samplePerBlockExpected);
    gainEffect.reset();
    panEffect.reset();
}

void InputProcessor::process(juce::AudioBuffer<float>& in)
{   
    //pan follows the knob
    gainEffect.set_gain_type(GAIN_TYPE::LINEAR);
    gainEffect.set_multiplier(inputGainLinear);
    panEffect.set_pan_value(inputPan);
    // juce does not interleave their buffers, and this makes sense from
    // a cache coherence reason!!! It also makes it easier to parallelize
    // the code holy shit my cs classes are teaching me things
    auto* left = in.getWritePointer(0);
    auto* right = in.getWritePointer(1);
    size_t numSamples = in.getNumSamples();
    for(size_t i = 0; i < numSamples; ++i)
    {
        //gain first
        left[i] = gainEffect.process(left[i]); // for one sample
        right[i] = gainEffect.process(right[i]); // so we do it twice
        //then pan
        panEffect.process(left[i], right[i]); // for two samples
    }
    // to_process = panEffect.process(to_process);
}