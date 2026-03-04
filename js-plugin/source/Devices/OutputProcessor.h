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

class OutputProcessor : public AudioDevice
{
    public:
    OutputProcessor(OutputParameters& op);

    void prepare(double sampleRate, int samplesPerBlockExpected) override;
    void process(juce::AudioBuffer<float>& in) override;

    // two consts. exist here, the first one (const Measurement&) says 
    // "we cannot modify the reference Measurement& being returned"
    // the second one (left() const) says 
    // "the function is not allowed to modify Measurement&"
    const Measurement& left() const noexcept { return levelL; }
    const Measurement& right() const noexcept { return levelR; }

    private:
    OutputParameters& outputParams;
    gain gainEffect;
    panner panEffect;
    clipper clipperEffect;
    Measurement levelL, levelR;
};

#endif