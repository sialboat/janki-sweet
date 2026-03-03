#include "OutputProcessor.h"

OutputProcessor::OutputProcessor() : gainEffect(), panEffect(), clipperEffect() {}

void OutputProcessor::prepare(double sampleRate, int samplesPerBlockExpected)
{
    gainEffect.reset();
    panEffect.reset();
    clipperEffect.reset();
}

void OutputProcessor::process(juce::AudioBuffer<float>& buffer)
{
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);
    size_t numSamples = buffer.getNumSamples();

    for(size_t i = 0; i < numSamples; i++) {
        left[i] = gainEffect.process(left[i]);
        right[i] = gainEffect.process(right[i]);

        panEffect.process(left[i], right[i]);

        left[i] = clipperEffect.process(left[i]);
        right[i] = clipperEffect.process(right[i]);
    }
}