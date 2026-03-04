#pragma once

#ifndef GUI_COMPONENT_H
#define GUI_COMPONENT_H

#include <juce_gui_basics/juce_gui_basics.h>                // for juce::Graphics
#include <juce_audio_processors/juce_audio_processors.h>    // for juce::APVTS
#include "Params/Parameters.h"                              // for linking GUI objects with Parameters

/*
    GUIComponent

    Base component inheriting from Juce::Component for use as a GUI Component. This is meant
    to be used as an object that aggregates various parts of a distinct plugin section
    within the Audio Plugin into one so we have minimal code within the main PluginEditor.
*/
class GUIComponent : public juce::Component
{
    public:
    GUIComponent(juce::AudioProcessorValueTreeState& _apvts, 
        Parameters& p) : apvts(_apvts), params(p) {}

    /* 
        Draw using juce::Graphics any visuals that may pertain to the component.
        Since this component is typically used for aggregating other components
        like buttons and knobs or elements within the GUI subdirectory, this shouldn't
        have much to implement typically.
    */ 
    virtual void paint(juce::Graphics& g) override = 0;

    /*
        Set bounds and the positional layout of where different components belong
    */
    virtual void resized() override = 0;

    private:
    // [[maybe_unused]] to prevent juce from screaming
    [[maybe_unused]] juce::AudioProcessorValueTreeState& apvts;
    [[maybe_unused]] Parameters& params;
};

#endif