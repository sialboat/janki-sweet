cmake_minimum_required(VERSION 3.22)

set(PARAM_SOURCES
    InputParameters.cpp

)

set(PARAM_HEADERS
    Parameters.h
    ParameterWrapper.h
    InputParameters.h
)
# interface for when it's only headers, no compiler sources needed i think
#
# Practical Rules
# Case	                        Recommended
# Header-only utility library	add_library(Name INTERFACE) + INTERFACE include dirs
# 
# Library with .cpp sources	    add_library(Name STATIC/SHARED) + PUBLIC include dirs
# 
# Internal sources              PRIVATE include dirs
# (only for target itself)	    
#
add_library(PARAMS STATIC
    ${PARAM_SOURCES}
    ${PARAM_HEADERS}
)

target_include_directories(PARAMS
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(JANKI_SWEET PRIVATE PARAMS)