#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), 
    inputSection(p.getAPVTS(), p.getInputParams(), *dynamic_cast<InputProcessor*>(&p.getAudioDevice(INPUT_INDEX))),
    outputSection(p.getAPVTS(), p.getOutputParams(), *dynamic_cast<OutputProcessor*>(&p.getAudioDevice(OUTPUT_INDEX)))
{
    juce::ignoreUnused (processorRef);
    addAndMakeVisible(inputSection);
    addAndMakeVisible(outputSection);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (520, 260);

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

    // ah shit we should probably use these maybe for the subcomponent resized() methods...
    auto panel = getLocalBounds().reduced (30);
    auto area = getLocalBounds().reduced (20);
    auto left = panel.removeFromLeft (140);
    auto right = panel.removeFromRight (140);

    inputSection.setBounds(10, 10, 200, 260);
    outputSection.setBounds(inputSection.getRight() + 10, 10, 200, 260);
}
