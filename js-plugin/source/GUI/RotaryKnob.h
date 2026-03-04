
#pragma once

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#define DEFAULT_KNOB_WIDTH 64
#define DEFAULT_KNOB_HEIGHT 64
#define DEFAULT_ROTARY_HEIGHT 80
#define DEFAULT_TEXT_HEIGHT 16

class RotaryKnob : public juce::Component
{
    public:
    RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& paramID, bool drawFromMiddle = false, int w = DEFAULT_KNOB_WIDTH, 
        int knobH = DEFAULT_KNOB_HEIGHT, int textH = DEFAULT_TEXT_HEIGHT);
    ~RotaryKnob() override;

    void resized() override;    

    juce::Slider slider;
    juce::Label label;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    private:
    int knobHeight = 0;
    int textHeight = 0;
    int width = 0;
};