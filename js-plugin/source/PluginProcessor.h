// PluginProcessor.h
#pragma once

#include <vector>
#include <juce_audio_processors/juce_audio_processors.h>
#include "Params/InputParameters.h"
#include "Devices/InputProcessor.h"

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getAPVTS() { return apvts; }

    //==============================================================================
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        juce::AudioProcessorValueTreeState::ParameterLayout l;

        auto inputs = InputParameters::createParameterGroup();
        if (inputs != nullptr)
            l.add(std::move(inputs->group));

        autio outputs = outputParameters::createParameterGroup();
        if (outputs != nullptr)
            l.add(std::move(outputs->group));
        return l;
        
    }

    float getInputPeak() const noexcept;
    float getOutputPeak() const noexcept;
private:
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    juce::AudioProcessorValueTreeState apvts;


    std::vector<std::unique_ptr<Parameters>> parameters;

    // we will eventually fit all of the special processors in data structures but not this one
    // or the output one and also I'm lazy
    InputProcessor inputProcessor; 
    // std::vector<std::unique_ptr<AudioDevice>> processors;
    // std::unique_ptr<InputParameters> inputParameters;
    

    //==============================================================================
    std::atomic<float> inputPeak {0.0f};
    std::atomic<float> outputPeak {0.0f};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
