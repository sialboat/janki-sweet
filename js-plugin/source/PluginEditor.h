#pragma once

#include "PluginProcessor.h"
#include "GUI/RotaryKnob.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    void timerCallback() override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    // RotaryKnob inputGain{};


    RotaryKnob inputKnob;
    RotaryKnob outputKnob;

    float inputMeter = 0.0f;
    float outputMeter = 0.0f;
    juce::Rectangle<int> meterArea;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
