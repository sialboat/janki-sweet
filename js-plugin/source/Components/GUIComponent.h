#pragma once

#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include <juce_gui_basics/juce_gui_basics.h>                // for juce::Graphics
#include <juce_audio_processors/juce_audio_processors.h>    // for juce::APVTS
#include "Params/Parameters.h"                              // for linking GUI objects with Parameters

/*
    GUIComponent

    Base component inheriting from Juce::Component for use as a GUI Component.
*/
class GUIComponent : public juce::Component
{
    public:
    GUIComponent(juce::AudioProcessorValueTreeState& _apvts, 
        Parameters& p) : apvts(_apvts), params(p) {}

    virtual void paint(juce::Graphics& g) override = 0;
    virtual void resized() override = 0;

    private:
    [[maybe_unused]] juce::AudioProcessorValueTreeState& apvts;
    [[maybe_unused]] Parameters& params;
};

#endif