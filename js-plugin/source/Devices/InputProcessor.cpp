// InputProcessor.cpp
#include "InputProcessor.h"

InputProcessor::InputProcessor() : gainEffect(), panEffect()
{}

InputProcessor::InputProcessor([[maybe_unused]] InputParameters& p) : gainEffect(), panEffect()
{}
/*
    Resets all DSP objects within the InputProcessor
*/
void InputProcessor::prepare([[maybe_unused]]double sampleRate, [[maybe_unused]]int samplePerBlockExpected)
{
    juce::ignoreUnused(sampleRate, samplePerBlockExpected);
    gainEffect.reset();
    panEffect.reset();
    levelL.reset();
    levelR.reset();
}

/*
    Applies the DSP effects on a sample-by-sample basis to the incoming juce::AudioBuffer.

    In the case of the InputProcessor, this is a simple pan and input gain.
*/
void InputProcessor::process(juce::AudioBuffer<float>& in)
{   
    //pan follows the knob

    // we don't need this because the GainEffect constructor does this for us by
    // default.
    // gainEffect.set_gain_type(GAIN_TYPE::LINEAR);
    // gainEffect.set_multiplier(inputGainLinear);
    // panEffect.set_pan_value(inputPan);
    
    // juce does not interleave their buffers, and this makes sense from
    // a cache coherence reason!!! It also makes it easier to parallelize
    // the code holy shit my cs classes are teaching me things
    auto* left = in.getWritePointer(0);
    auto* right = in.getWritePointer(1);
    float maxL = 0.0f, maxR = 0.0f;
    size_t numSamples = in.getNumSamples(); // num samples per channel
    for(size_t i = 0; i < numSamples; ++i)
    {
        //gain first
        left[i] = gainEffect.process(left[i]); // for one sample
        right[i] = gainEffect.process(right[i]); // so we do it twice
        //then pan
        panEffect.process(left[i], right[i]); // for two samples
        maxL = std::max(left[i], maxL);
        maxR = std::max(right[i], maxR);
    }
    levelL.updateIfGreater(maxL);
    levelR.updateIfGreater(maxR);
    // to_process = panEffect.process(to_process);
}