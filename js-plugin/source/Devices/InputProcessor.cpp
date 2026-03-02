#include "InputProcessor.h"

InputProcessor::InputProcessor() : gainEffect(), panEffect()
{}

/*
    Resets all DSP objects within the InputProcessor
*/
void InputProcessor::prepare([[maybe_unused]]double sampleRate, [[maybe_unused]]int samplePerBlockExpected)
{
    gainEffect.reset();
    panEffect.reset();
}

/*
    Applies the DSP effects on a sample-by-sample basis to the incoming juce::AudioBuffer.

    In the case of the InputProcessor, this is a simple pan and input gain.
*/
void InputProcessor::process(juce::AudioBuffer<float>& in)
{
    // juce does not interleave their buffers, and this makes sense from
    // a cache coherence reason!!! It also makes it easier to parallelize
    // the code holy shit my cs classes are teaching me things
    auto* left = in.getWritePointer(0);
    auto* right = in.getWritePointer(1);
    size_t numSamples = in.getNumSamples(); // num samples per channel
    for(size_t i = 0; i < numSamples; ++i)
    {
        panEffect.process(left[i], right[i]); // for two samples
        gainEffect.process(left[i]); // for one sample
        gainEffect.process(right[i]); // so we do it twice
    }
    // to_process = panEffect.process(to_process);
}