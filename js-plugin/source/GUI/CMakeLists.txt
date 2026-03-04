cmake_minimum_required(VERSION 3.22)

set(GUI_SOURCES
    RotaryKnob.cpp
)

set(GUI_HEADERS
    RotaryKnob.h
    Themes.h
    MultiStateButton.h
)

add_library(GUI STATIC
    ${GUI_SOURCES}
    ${GUI_HEADERS}
)

target_sources(JANKI_SWEET PRIVATE
    ${GUI_SOURCES}
    ${GUI_HEADERS}
)

target_include_directories(GUI
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(LookAndFeel)

target_link_libraries(GUI PRIVATE JUCE_HEADERS)
target_link_libraries(JANKI_SWEET PUBLIC GUI)