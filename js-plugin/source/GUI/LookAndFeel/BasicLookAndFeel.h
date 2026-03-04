#pragma once

#ifndef BASIC_LOOK_AND_FEEL_H
#define BASIC_LOOK_AND_FEEL_H


//font class
#include <juce_gui_basics/juce_gui_basics.h>
class Fonts
{
public:
    Fonts() = delete;
    static juce::Font getFont(float height = 16.0f);
private:
    static const juce::Typeface::Ptr typeface;
};

//main look and feel class
class MainLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MainLookAndFeel();
    
    juce::Font getLabelFont(juce::Label&) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainLookAndFeel)
};


#endif