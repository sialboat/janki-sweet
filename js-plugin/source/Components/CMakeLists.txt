# CMakeLists.txt for Components folder

cmake_minimum_required(VERSION 3.22)

set(COMPONENTS_SOURCE
    InputComponent.cpp
    OutputComponent.cpp
    LevelMeter.cpp
)

set(COMPONENTS_HEADERS
    InputComponent.h
    OutputComponent.h
    LevelMeter.h
    GUIComponent.h
)

add_library(COMPONENTS
    STATIC
        ${COMPONENTS_SOURCE}
        ${COMPONENTS_HEADERS}
)

target_link_libraries(COMPONENTS
    PRIVATE
        JUCE_HEADERS
        GUI
        AUDIO_DEVICES
        UTILS
    PUBLIC
        PARAMS
)

target_link_libraries(JANKI_SWEET
    PUBLIC
        COMPONENTS
)

target_include_directories(COMPONENTS
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

