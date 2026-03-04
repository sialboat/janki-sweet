#pragma once

#ifndef OUTPUT_PROCESSOR_H
#define OUTPUT_PROCESSOR_H

#include <juce_audio_processors/juce_audio_processors.h>
#include "Devices/AudioDevice.h"
#include "Utils/Measurement.h"
#include "Params/OutputParameters.h"
#include "le-janky/clipper.h"
#include "le-janky/gain.h"
#include "le-janky/panning.h"

/*
    OutputProcessor

    Audio Device reducing the DSP components within the Output Processor 
    (Gain, Bypass, Meters, Pan effect, clipping) to two methods:
    prepare() and process().
*/
class OutputProcessor : public AudioDevice
{
    public:
    OutputProcessor(OutputParameters& op);

    // Allocate memory and initialize DSP primitives
    void prepare(double sampleRate, int samplesPerBlockExpected) override;

    // process samples within juce::AudioBuffer.
    void process(juce::AudioBuffer<float>& in) override;

    // Get the left and right measurement values for passing metering information
    Measurement& left() noexcept { return levelL; }
    Measurement& right() noexcept { return levelR; }

    // const Measurement& left() const noexcept { return levelL; }
    // const Measurement& right() const noexcept { return levelR; }

    private:
    OutputParameters& outputParams;
    gain gainEffect;
    panner panEffect;
    clipper clipperEffect;
    Measurement levelL, levelR;
};

#endif