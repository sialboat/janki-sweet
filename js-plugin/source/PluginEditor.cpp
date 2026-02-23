#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), 
    inputKnob ("Input", processorRef.apvts, juce::ParameterID {"inputGain", 1}),
    outputKnob ("Output", processorRef.apvts, juce::ParameterID {"outputGain", 1})
{
    addAndMakeVisible (inputKnob);
    addAndMakeVisible (outputKnob);
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (520, 260);
    startTimerHz (30);

}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    auto panel = getLocalBounds().reduced (30);
    g.setColour (juce::Colours::white);

    auto box = getLocalBounds().reduced (40);
    g.fillRect (box);

    g.setColour (juce::Colours::white);
    g.drawRect(box, 2);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto panel = getLocalBounds().reduced (30);
    auto area = getLocalBounds().reduced (20);
    auto left = panel.removeFromLeft (140);
    auto right = panel.removeFromRight (140);
    meterArea = panel.reduced (30,20);

    inputKnob.setBounds (left.reduced (20));
    outputKnob.setBounds (right.reduced (20));
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    // temporary until meter wiring is done
    repaint();
}
