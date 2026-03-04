# info

If there is anything significant / important that has been changed within the codebase we can put it here

## Codebase Organization

The codebase is organized into subdirectories as follows:

- **Components**: files that aggregate related GUI objects into one file. Abstracts the GUI objects into 
    `paint()` and `resized()` methods.
  - For example, if an effect that was implemented was a `Distortion`, a `DistortionComponent` would also need to be
    implemented to aggregate all of the GUI-related distortion component bits (drive knob, mix knob, distortion mode, etc.)
- **Devices**: files that aggregate Audio DSP related objects into one file. Abstracts DSP primitives into 
    `prepare()` and `process()` methods.
  - `process()` takes a `juce::AudioBuffer<float>&` object and will utilize the DSP primitives within `le-janky` to 
    process the buffer on a sample-by-sample basis.
  - these objects are vectorized in the main `PluginProcessor` files so a single for loop calling `process()`
    functions from all of the respective Audio Devices can be used.
- **GUI**: files that represent custom GUI objects that inherit from JUCE's Graphics system.
- **GUI/LookAndFeel**: files that implement custom LookAndFeels to GUI objects or other Components using the 
    JUCE Graphics system.
- **le-janky**: self-rolled DSP primitives. We use these instead of the JUCE library for two reasons:
  - So we can fucking learn what we are doing
  - Because we can
- **Params**: Files that aggregate JUCE-Parameter related objects to streamline parameter management.
  - Most notably is the file `ParameterWrapper.h`, a header containing objects that encapsulate all of
    the important functions that which a Parameter must do (`update()`, `smoothen()`, `reset()`, `prepare()`).
- **Utils**: Files that serve as small utilities that objects in other subdirectories rely on.

Typically, if a new section of the plugin is added with audio-processing capabilities, we should have the
following in each respective folder:

- **Components/`FeatureNameComponent`** compiling all GUI-adjacent objects pertaining to `FeatureName`.
- **Params/`FeatureNameParams`** compiling all audio parameters for JUCE's APVTS to talk to.
- **Devices/`FeatureNameProcessor`** compiling all DSP functionality pertaining to `FeatureName` into one location
    and two methods.
- **le-janky/`FeatureNamePrimitives`** compiling all DSP-related primitives used to process the incoming
    audio for `FeatureName`, given that DSP is required.
- **Utils/`Utilities-if-needed`**
*Assuming `FeatureName` is the feature name that is to be added.*

Additionally, we should have `FeatureNameComponent`, `FeatureNameParams`, and `FeatureNameProcessor` within the
respective `PluginProcessor` and `PluginEditor` files.

## Parameter Wrappers

<!-- %% TODO %% -->

## Components Structure

<!-- %% TODO %% -->
