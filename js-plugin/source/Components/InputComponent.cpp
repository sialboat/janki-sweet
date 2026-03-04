#include "InputComponent.h"

InputComponent::InputComponent(juce::AudioProcessorValueTreeState& _apvts, 
    InputParameters& ip, InputProcessor& _ip) : GUIComponent(_apvts, ip),
    inGainKnob("Input Gain", _apvts, ip.getInputParams().inGainParam->getParamID(), true), // holy boilerplate
    inPanKnob("Output Gain", _apvts, ip.getInputParams().inGainParam->getParamID(), true),
    inputMeter(_ip.left(), _ip.right())
{
    addAndMakeVisible(inGainKnob);
    addAndMakeVisible(inPanKnob);
    addAndMakeVisible(inputMeter);
    // addAndMakeVisible(meterArea);

    setSize(200, 260); // arbitrary, subject to change
    // startTimerHz(30);
}

void InputComponent::paint(juce::Graphics& g)
{}

void InputComponent::resized()
{
    auto bounds = getLocalBounds();
    inGainKnob.setBounds(10, 50, DEFAULT_KNOB_WIDTH, DEFAULT_ROTARY_HEIGHT);
    inPanKnob.setBounds(10, inGainKnob.getBottom() + 10, DEFAULT_KNOB_WIDTH, DEFAULT_ROTARY_HEIGHT);
    inputMeter.setBounds(bounds.getRight() - 10, bounds.getBottom() - 20, 48, 128);
    meterArea.setBounds(bounds.getRight() - 10, bounds.getBottom() - 20, 48, 128);
}

// void InputProcessor::timerCallback()
// {
//     // temporary until meter wiring is done
//     repaint();
// }