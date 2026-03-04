// PluginProcessor.h
#pragma once

#include <vector>
#include <juce_audio_processors/juce_audio_processors.h>
#include "Params/InputParameters.h"
#include "Params/OutputParameters.h"
#include "Devices/InputProcessor.h"
#include "Devices/OutputProcessor.h"

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

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


    // these may be broken use the ones below
    Parameters& getParameterObject(size_t i) { return *parameters.at(i).get(); }
    AudioDevice& getAudioDevice(size_t i) { return *processors.at(i).get(); }

    // these
    InputParameters& getInputParams() { return *dynamic_cast<InputParameters*>(parameters.at(INPUT_INDEX).get()); }
    OutputParameters& getOutputParams() { return *dynamic_cast<OutputParameters*>(parameters.at(OUTPUT_INDEX).get()); }
    InputProcessor& getInputProcessor() { return *dynamic_cast<InputProcessor*>(processors.at(INPUT_INDEX).get()); }
    OutputProcessor& getOutputProcessor() { return *dynamic_cast<OutputProcessor*>(processors.at(OUTPUT_INDEX).get()); }


private:
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    juce::AudioProcessorValueTreeState apvts;


    std::vector<std::unique_ptr<Parameters>> parameters;        // All Parameter Vectors
    std::vector<std::unique_ptr<AudioDevice>> processors;       // All Processor Vectors

    // we will eventually fit all of the special processors in data structures but not this one
    // or the output one and also I'm lazy
    // InputProcessor inputProcessor; 
    // std::unique_ptr<InputParameters> inputParameters;

    
    template <typename PARAMETER_TYPE>
    void createAndPushParameters() {
        parameters.push_back(std::make_unique<PARAMETER_TYPE>(apvts));
    }

    template <typename PARAMETER_TYPE, typename PROCESSOR_TYPE>
    void createAndPushProcessor(size_t i) {
        auto& paramPointer = parameters.at(i);
        if(auto* derived = dynamic_cast<PARAMETER_TYPE*>(paramPointer.get())) {
            processors.push_back(std::make_unique<PROCESSOR_TYPE>(*derived));
        }
    }
    

    //==============================================================================
    // std::atomic<float> inputPeak {0.0f};
    // std::atomic<float> outputPeak {0.0f};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
