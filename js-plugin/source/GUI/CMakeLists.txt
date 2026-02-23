cmake_minimum_required(VERSION 3.22)

target_sources(JANKI_SWEET PRIVATE
    RotaryKnob.cpp
    RotaryKnob.h
    Themes.h
)

add_subdirectory(LookAndFeel)
