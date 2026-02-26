#pragma once

#ifndef THEMES_H
#define THEMES_H

/*
    Themes.h

    Contains namespaces and whatever constants that we need to set looks and feels, color palettes, etc. 

    ...at least until we solidify a GUI direction this is what we're working with at least with the
    JUCE graphics engine
*/

namespace Colors
{
    namespace LevelMeter
    {
        const juce::Colour background {245, 240, 235};
        const juce::Colour tickLine {200, 200, 200};
        const juce::Colour tickLabel {80, 80, 80};
        const juce::Colour tooLoud {226, 74, 81};
        const juce::Colour levelOK {65, 206, 88};
    }
}

#endif