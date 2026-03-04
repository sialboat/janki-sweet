#include "OutputComponent.h"

OutputComponent::OutputComponent(juce::AudioProcessorValueTreeState& _apvts, 
    OutputParameters& op, OutputProcessor& _op) : GUIComponent(_apvts, op),
    outGainKnob("Output Gain", _apvts, op.getOutputParams().outGainParam->getParamID(), true),
    outPanKnob("Output Pan", _apvts, op.getOutputParams().outputPan->getParamID()),
    mixKnob("Mix", _apvts, op.getOutputParams().mixParam->getParamID()),
    clipperButton(_apvts, op.getOutputParams().clipModeParam->getParam()->paramID, op.getClipperModes()), // holy boilerplate
    outMeter(_op.left(), _op.right())
{
    addAndMakeVisible(outGainKnob);
    addAndMakeVisible(outPanKnob);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(clipperButton);
    addAndMakeVisible(outMeter);
    // addAndMakeVisible(meterArea);

    bypassButton.setButtonText("Bypass");
    addAndMakeVisible(bypassButton);

    setSize(200, 260);
}

void OutputComponent::paint(juce::Graphics& g)
{}

void OutputComponent::resized()
{
    auto bounds = getLocalBounds();

    outGainKnob.setBounds(10, 50, DEFAULT_KNOB_WIDTH, DEFAULT_ROTARY_HEIGHT);
    outPanKnob.setBounds(10, outGainKnob.getBottom() + 10, DEFAULT_KNOB_WIDTH, DEFAULT_ROTARY_HEIGHT);
    mixKnob.setBounds(10, outPanKnob.getBottom() + 10, DEFAULT_KNOB_WIDTH, DEFAULT_ROTARY_HEIGHT);
    clipperButton.setBounds(outGainKnob.getRight() + 10, 50, 48, 24);
    bypassButton.setBounds(clipperButton.getRight() + 10, 50, 48, 24);
    outMeter.setBounds(bounds.getRight() - 10, bounds.getBottom() - 20, 48, 128);
    meterArea.setBounds(bounds.getRight() - 10, bounds.getBottom() - 20, 48, 128);
}