#pragma once

#ifndef OUTPUT_PROCESSOR_H
#define OUTPUT_PROCESSOR_H

#include <juce_audio_processors/juce_audio_processors.h>
#include "le-janky/clipper.h"
#include "le-janky/gain.h"
#include "le-janky/panning.h"

class OutputProcessor : public AudioDevice
{
    public:
    OutputProcessor();

    void prepare(double sampleRate, int samplesPerBlockExpected) override;
    void process(juce::AudioBuffer<float>& in) override;

    private:
    gain gainEffect;
    panner panEffect;
    clipper clipperEffect;
};

#endif