#pragma once

#ifndef OUTPUT_COMPONENT_H
#define OUTPUT_COMPONENT_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_events/juce_events.h>
#include "LevelMeter.h"
#include "Components/GUIComponent.h"
#include "GUI/MultiStateButton.h"
#include "GUI/RotaryKnob.h"
#include "Params/OutputParameters.h"
#include "Devices/OutputProcessor.h"

/*
    OutputComponent

    Juce::Component that compiles all of the output-related components.
*/
class OutputComponent : public GUIComponent
{
    public:
    OutputComponent(juce::AudioProcessorValueTreeState& _apvts, 
        OutputParameters& op, OutputProcessor& _op);

    void paint(juce::Graphics& g) override;
    void resized() override;

    private:

    RotaryKnob outGainKnob;
    RotaryKnob outPanKnob;
    RotaryKnob mixKnob;
    MultiStateButton clipperButton;

    LevelMeter outMeter;
    juce::Rectangle<int> meterArea;
    juce::TextButton bypassButton;

};

#endif