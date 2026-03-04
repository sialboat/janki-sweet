#pragma once

#ifndef METER_H
#define METER_H

// #include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include "Utils/Measurement.h"
#include "GUI/Themes.h"

class LevelMeter : public juce::Component,
                   private juce::Timer
{
    public:
    LevelMeter(Measurement& left, Measurement& right);
    ~LevelMeter() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    private:

    void timerCallback() override;

    // maps db level to pixels on screen
    int positionForLevel(float dbLevel)
    {
        return int(std::round(juce::jmap(dbLevel, maxdB, mindB, maxPos, minPos)));
    }

    void drawLevel(juce::Graphics& g, float level, int x, int w);
    void updateLevel(float newLevel, float& smoothValue, float& leveldB) const;

    const Measurement& leftMeasurement;
    const Measurement& rightMeasurement;
    
    static constexpr float maxdB = 6.0f;
    static constexpr float mindB = -60.0f;
    static constexpr float stepdB = 6.0f;
    
    float maxPos = 0.0f;
    float minPos = 0.0f;
    
    static constexpr float clampdB = -120.0f;
    static constexpr float clampLevel = 0.000001f; //-120dB, this is our -infinity    
    
    float dbLevelL;
    float dbLevelR;
    
    // change this value internally for num. of updates
    static constexpr int refreshRate = 60; 
    
    float decay = 0.0f;
    float levelL = clampLevel;
    float levelR = clampLevel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelMeter)
};

#endif