
#pragma once

#include <JuceHeader.h>

class RotaryKnob : public juce::Component
{
    public:
    RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& paramID, bool drawFromMiddle = false, int w, int knobH, int textH);
    ~RotaryKnob() override;

    void resized() override;

    juce::Slider slider;
    juce::Label label;

    juce::AudioProcessorValueTreeState::SliderAttachent attachment;

    private:
    int knobHeight = 0;
    int textHeight = 0;
    int width = 0;

}