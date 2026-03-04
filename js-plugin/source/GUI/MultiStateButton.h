#pragma once

#ifndef MULTISTATE_BUTTON_H
#define MULTISTATE_BUTTON_H

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>

/*
    MultiStateButton class

    Juce::TextButton that allows for the management of multiple states (more than just
    an ON and OFF). This is useful if you wish to have a button be able to cycle
    between LFO cycles (SAW, SQUARE, SINE, TRIANGLE, RANDOM) and do not want to use
    a ComboBox.
*/
class MultiStateButton : public juce::TextButton
{
    public:
    MultiStateButton(juce::AudioProcessorValueTreeState& _apvts, const juce::String& _paramID,
         const juce::StringArray _choices) : choices(_choices), choiceIndex(0),
         buttonAttachment(_apvts, _paramID, *this)
    {
        setButtonText(choices[choiceIndex]);
        onClick = [this] { cycleStates(); };
    }

    private:
    juce::StringArray choices;
    size_t choiceIndex;

    // this is how we let the parameter talk to an audio parameter.
    juce::AudioProcessorValueTreeState::ButtonAttachment buttonAttachment;

    void cycleStates() {
        choiceIndex++;
        if(choiceIndex < choices.size())
            choiceIndex = 0;
        setButtonText(choices[choiceIndex]);
    }
};

#endif