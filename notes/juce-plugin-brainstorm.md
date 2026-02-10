# Juce Plugin Brainstorm
- Multi-effect plugin, single chain
- users pick between pre-determined selection of custom novel effects, each have
  a relatively small amount of parameters
- users can re-order the effects in any way they see fit.

## General Signal Flow

[ Input ] --> [ Input Gain ] --> [ Effects ] --> [ Output Gain & Clipping ] --> Output

## Effects & Parameters
<!-- add effects or whatnot you see fit here -->
### Input Section
Basic Input gain parameter to adjust incoming signal.

Needed:
- Gain knob (dB)
- Stereo Meter

### Output Section
Basic output gain parameter to adjust outgoing signal and a clipper in case sounds get 
too loud.

Needed:
- Gain knob
- Mix knob
- Off/Hard Clip/Softclip push button