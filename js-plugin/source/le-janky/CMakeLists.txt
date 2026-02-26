cmake_minimum_required(VERSION 3.22)

set(LE_JANKY_SOURCES
    DelayLine.cpp
    gain.cpp
    panning.cpp
)

set(LE_JANKY_HEADERS
    Buffer.h
    DelayLine.h
    gain.h
    panning.h
)

add_library(LE_JANKY STATIC
    ${LE_JANKY_SOURCES}
    ${LE_JANKY_HEADERS}
)

target_include_directories(LE_JANKY
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(LE_JANKY PUBLIC UTILS) # this is needed so dsp files have the math utils
target_link_libraries(JANKI_SWEET PRIVATE LE_JANKY)