#pragma once

#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_events/juce_events.h>    // Timer
#include "Params/InputParameters.h"
#include "Devices/InputProcessor.h"
#include "Components/GUIComponent.h"
#include "LevelMeter.h"
#include "GUI/RotaryKnob.h"

/*
    InputComponent

    Juce::Component that aggregates all of the input-related components into one
    Includes
        - Input Gain Knob
        - Input Pan Knob
        - Input Meter
        - Rectangle Meter Area
*/
class InputComponent : public GUIComponent
{
    public:
    InputComponent(juce::AudioProcessorValueTreeState& _apvts, 
        InputParameters& ip, InputProcessor& _ip);

    void paint(juce::Graphics& g) override;
    void resized() override;
    // void timerCallback() override;

    private:
    RotaryKnob inGainKnob;
    RotaryKnob inPanKnob;
    LevelMeter inputMeter;
    juce::Rectangle<int> meterArea;
};

#endif