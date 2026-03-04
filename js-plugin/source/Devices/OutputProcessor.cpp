#include "OutputProcessor.h"

OutputProcessor::OutputProcessor(OutputParameters& op) : outputParams(op), gainEffect(),
    panEffect(), clipperEffect() {}

/*
    Allocate memory and/or initialize DSP primitives
*/
void OutputProcessor::prepare(double sampleRate, int samplesPerBlockExpected)
{
    gainEffect.reset();
    panEffect.reset();
    clipperEffect.reset();
    levelL.reset();
    levelR.reset();
}

/*
    Process samples within juce::AudioBuffer
*/
void OutputProcessor::process(juce::AudioBuffer<float>& buffer)
{
    auto* left = buffer.getWritePointer(0);
    auto* right = buffer.getWritePointer(1);
    float maxL = 0.0f, maxR = 0.0f;
    size_t numSamples = buffer.getNumSamples();

    for(size_t i = 0; i < numSamples; i++) {
        // if not bypassed, do this
        if(!outputParams.getOutputParams().bypassParam->getValue()) {
            left[i] = gainEffect.process(left[i]);
            right[i] = gainEffect.process(right[i]);
    
            panEffect.process(left[i], right[i]);
    
            left[i] = clipperEffect.process(left[i]);
            right[i] = clipperEffect.process(right[i]);
            
            maxL = std::max(left[i], maxL);
            maxR = std::max(right[i], maxR);
        }
    }

    levelL.updateIfGreater(maxL);
    levelR.updateIfGreater(maxR);
}