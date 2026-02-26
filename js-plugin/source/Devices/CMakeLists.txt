# this has yet to exist but the folder will house our other random devices

# cmake_minimum_required(VERSION 3.22)

set(AUDIO_DEVICES_SOURCES
    InputProcessor.cpp
    LevelMeter.cpp
)

set(AUDIO_DEVICES_HEADERS
    InputProcessor.h
    LevelMeter.h
    AudioDevice.h
)

add_library(AUDIO_DEVICES STATIC
    ${AUDIO_DEVICES_HEADERS}
    ${AUDIO_DEVICES_SOURCES}
)

target_include_directories(AUDIO_DEVICES
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(AUDIO_DEVICES 
    PRIVATE
        juce::juce_audio_processors
        juce::juce_audio_basics
        juce::juce_graphics
        juce::juce_core # Often needed for certain parameter types
)

target_link_libraries(AUDIO_DEVICES PRIVATE GUI)
target_link_libraries(AUDIO_DEVICES PRIVATE LE_JANKY) # this is needed so dsp files have the math utils
target_link_libraries(AUDIO_DEVICES PRIVATE UTILS) # this is needed so dsp files have the math utils

# target_link_libraries(JANKI_SWEET PUBLIC AUDIO_DEVICES)