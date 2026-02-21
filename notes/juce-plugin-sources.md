Markdown file documenting potential sources and notes (if any) that may be of use for developing plugin

https://docs.juce.com/master/classjuce_1_1AudioProcessorGraph.html

https://docs.juce.com/master/classjuce_1_1AudioProcessor.html

https://juce.com/tutorials/tutorial_audio_processor_graph/

https://forum.juce.com/t/released-a-new-juce-programming-course-multi-effect-plugin/57379

https://musicinformationretrieval.com/intro.html

# Sample subfolder `CMakeList.txt`:

```python
# set the required CMake version
cmake_minimum_required(VERSION 3.22)

# put all header files here (*.h), replace SUBFOLDER_NAME with the 
# header files within SUBFOLDER_NAME, append _HEADERS for naming consistency
set(SUBFOLDER_NAME_HEADERS
    # headers go here
)

# put all source cpp files here (*.cpp), replace SUBFOLDER_NAME with the
# header files within SUBFOLDER_NAME, append _SOURCES for naming consistency
set(SUBFOLDER_NAME_SOURCES 
    # source files go here
)

add_library(SUBFOLDER_NAME
    STATIC
    ${SUBFOLDER_NAME_HEADERS}
    ${SUBFOLDER_NAME_SOURCES}
)

target_include_directories(SUBFOLDER_NAME
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PROJECT_NAME PRIVATE SUBFOLDER_NAME)
```

In the global `CMakeList.txt`:
```python

...

add_subdirectory(path/to/folder)

...
```

### `PUBLIC` vs `PRIVATE` vs `STATIC` vs `INTERFACE`:
- Header only utilities $\implies$ `add_library(NAME INTERFACE)` + `target_include_directories(NAME INTERFACE)`
- Library with `.cpp` sources $\implies$ `add_library(NAME STATIC/SHARED)` + `PUBLIC include dirs`
- Internal sources $\implies$ `PRIVATE include dirs`

`include_dirs` $\implies$ `target_include_directories`

- `STATIC`: compiles to `.a` or `.lib`, for when libraries/multiple files need to link to another target, common for dsp library
- `SHARED`: compiles to `.so` or `.dll`, for when multiple executables must share the same library at runtime, rare for juce plugins
- `INTERFACE`: for header-only targets, does not compile, only keeps track of include dirs, compile flags, link libraries, 
  header-only utilities or fuck tons of templates
- `OBJECT`: advanced; compiles into object files