cmake_minimum_required(VERSION 3.22)

set(UTILS_HEADERS
    small_math.h
    Measurement.h
)
set(UTILS_SOURCES
)

# message(STATUS "UTILS include path: ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(UTILS INTERFACE
    # ${UTILS_HEADERS}
)

target_include_directories(UTILS
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(JANKI_SWEET PRIVATE UTILS)