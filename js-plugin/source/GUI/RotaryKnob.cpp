#include "UI/RotaryKnob.h"
// #include "LookAndFeel.h"

RotaryKnob::RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts,
    const juce::ParameterID& paramID, bool drawFromMiddle, int w, int knobH, int textH) : 
    attachment(apvts, paramID.getParamID(), slider), width(w), knobHeight(knobH), 
    textHeight(textH)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, width, textHeight);
    slider.setBounds(0, 0, width, knobHeight);
    addAndMakeVisible(slider);

    label.setText(text, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::dontSendNotification);
    label.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setSize(w, textH, knobH);

    // setLookAndFeel()

    float pi = juce::MathConstants<float>::pi;
    slider.setRotaryParameters(1.25f * pi, 2.75f * pi, true);
    slider.getProperties.set("drawFromMiddle", drawFromMiddle);

    // 225º and 495º for start and end == 1.25 * pi and 2.75 * pi. 
    // If we used 135º at the end, the angle would be drawn in the 
    // opposite way
}

RotaryKnob::~RotaryKnob() {}

void RotaryKnob::resized()
{
    slider.setTopLeftPosition(0, textHeight);
}