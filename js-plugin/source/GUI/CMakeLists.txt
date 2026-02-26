cmake_minimum_required(VERSION 3.22)

set(GUI_SOURCES
    RotaryKnob.cpp
)

set(GUI_HEADERS
    RotaryKnob.h
    Themes.h
)

target_sources(JANKI_SWEET PRIVATE
    ${GUI_SOURCES}
    ${GUI_HEADERS}
)

add_subdirectory(LookAndFeel)

target_link_libraries(JANKI_SWEET PUBLIC GUI)