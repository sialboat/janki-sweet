cmake_minimum_required(VERSION 3.22)

set(GUI_SOURCES

)

set(GUI_HEADERS
    BasicLookAndFeel.h
)

target_sources(JANKI_SWEET
    PRIVATE
        ${GUI_SOURCES}
        ${GUI_HEADERS}
)