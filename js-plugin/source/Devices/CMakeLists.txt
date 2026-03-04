# this has yet to exist but the folder will house our other random devices

cmake_minimum_required(VERSION 3.22)

set(AUDIO_DEVICES_SOURCES
    InputProcessor.cpp
    LevelMeter.cpp
)

set(AUDIO_DEVICES_HEADERS
    AudioDevice.h
    InputProcessor.h
    LevelMeter.h
)

add_library(AUDIO_DEVICES
    STATIC
        ${AUDIO_DEVICES_HEADERS}
        ${AUDIO_DEVICES_SOURCES}
)

target_link_libraries(AUDIO_DEVICES PRIVATE JUCE_HEADERS)
target_link_libraries(AUDIO_DEVICES PUBLIC PARAMS) 
target_link_libraries(AUDIO_DEVICES PRIVATE GUI)
target_link_libraries(AUDIO_DEVICES PRIVATE LE_JANKY) # this is needed so dsp files have the math utils
target_link_libraries(AUDIO_DEVICES PRIVATE UTILS) # this is needed so dsp files have the math utils
target_link_libraries(JANKI_SWEET PUBLIC AUDIO_DEVICES)

target_include_directories(AUDIO_DEVICES
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..   # <-- this lets #include "Params/..." resolve from source/
)