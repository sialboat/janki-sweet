#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/InputComponent.h"
#include "Components/OutputComponent.h"
#include "Params/InputParameters.h"
#include "Params/OutputParameters.h"
#include "Devices/InputProcessor.h"
#include "Devices/OutputProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    // void timerCallback() override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    InputComponent inputSection;
    OutputComponent outputSection;

    // std::vector<GUIComponent> components; // later we can transition into this

    // RotaryKnob inputKnob;
    // RotaryKnob outputKnob;

    // float inputMeter = 0.0f;
    // float outputMeter = 0.0f;
    // juce::Rectangle<int> meterArea;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
