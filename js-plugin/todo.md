# todo

## High Prio

- [ ] Reading Brian's Book (1-3) & Math of DFT
- [ ] Figure out how to test current code
- [ ] Check if the plugin fucking works
- [ ] add header files for each section (`utils.h` or a `params.h` etc. etc. so we do not need to include a million
      things from `Params` or `Utils`). We would have to rewrite a lot of includes though I think.
- [ ] Vectorize (as in the `std::vector` data structure, not the Linear Algebra primitive) the GUIComponents within
      `PluginEditor.h`
- [x] Input and Output sections
  - [x] Input Gain knob and meter
  - [x] Panning DSP Processor
  - [x] Clipping DSP Processor
  - [x] Input Gain DSP Processor

## Med Prio

- [x] Document `gain.h` and `gain.cpp`
- [x] Document new `le-janky` files (`clipper` and `panning`)
- [x] Maybe a bypass button as well? Should this be implemented in every component?
- [ ] Maybe add a *DIM* button in the Output Section? (reduces output by a flat amount to make things quieter)

## Low Prio

- [ ] Centralize documentation maybe?
