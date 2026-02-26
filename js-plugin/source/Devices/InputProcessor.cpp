#include "InputProcessor.h"

InputProcessor::InputProcessor() : gainEffect(GAIN_TYPE::DB_FS), panEffect()
{}

void InputProcessor::prepare(double sampleRatge, int samplePerBlockExpected)
{
    gainEffect.reset();
    panEffect.reset();
}

void InputProcessor::process(juce::AudioBuffer<float>& in)
{
    // juce does not interleave their buffers, and this makes sense from
    // a cache coherence reason!!! It also makes it easier to parallelize
    // the code holy shit my cs classes are teaching me things
    auto* left = in.getWritePointer(0);
    auto* right = in.getWritePointer(1);
    size_t numSamples = in.getNumSamples();
    for(size_t i = 0; i < numSamples; ++i)
    {
        panEffect.process(left[i], right[i]); // for two samples
        gainEffect.process(left[i]); // for one sample
        gainEffect.process(right[i]); // so we do it twice
    }
    // to_process = panEffect.process(to_process);
}