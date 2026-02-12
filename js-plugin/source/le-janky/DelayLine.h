
#pragma once

#ifndef DELAY_LINE_H
#define DELAY_LINE_H

#include "le-janky/Buffer.h"
#include "Utils/small_math.h"
#include <algorithm>

enum class INTERPOLATION_MODE {
    NEAREST_NEIGHBORS = 0,
    LINEAR = 1,
    CUBIC = 2,
    LAGRANGE = 3,
    HERMITE = 4,
    THIRAN = 5
};

class DelayLine
{
    public:
    DelayLine(alpha = 0.5f);
    DelayLine(size_t size, alpha = 0.5f, INTERPOLATION_MODE m = LAGRANGE);

    size_t getBufferLength() { return size; }
    size_t getReadIndex() { return readIndex; }
    size_t getWriteIndex() { return writeIndex; }
    void setReadIndex(size_t newIndex) { readIndex = newIndex; }
    void setWriteIndex(size_t newIndex) { writeIndex = newIndex; }
    void setOverwriteable(bool n) { canOverwrite = n; }
    bool isDataOverwritable() { return canOverwrite; }

    float getAlpha() { return alpha; }
    void setAlpha(float f) { alpha = f; }

    void setCapacity(size_t newCapacity);               // sets capacity to a larger length and zeros the buffer.

    float read();                                       // read at readIndex
    float readBehind(float i);                          // read i indices behind readIndex
    float readAt(float i);                              // read at index i

    void write(float in);                              // write in at writeIndex
    void writeAhead(float in, size_t i);               // write in i indices ahead writeIndex
    void writeBehind(float in, size_t i);              // write in i indices behind writeIndex
    void writeAt(float in, size_t i);                  // write in at index i

    void clear() { buffer.clear(); }                    // zero the buffer with buffer.clear();
    void reset();                                       // zero the buffer iteratively.

    private:
    float interpolate(float at = 0.0f);              // interpolateion algorithms at index at.
    float linear(float at = 0.0f);                   // linear interpolation
    float nearest_neighbors(float at = 0.0f);        // nearest neighbors interpolation
    float cubic(float at = 0.0f);                    // cubic interpol;ation
    float lagrange(float at = 0.0f);                 // lagrange interpolation
    float hermite(float at = 0.0f);                  // hermite interpolation
    float thiran(float at = 0.0f, int order);        // thiran allpass interpolation
    // float thiran_1(float at = 0.0f);                 // first order thiran interpolation

    private:
    // size_t size is implicitly defined via the buffer class.
    // can be accessed using buffer.size(); but this is inefficient so
    // we are just going to cache it.
    buffer<float> buffer;
    size_t readIndex;
    size_t writeIndex;
    size_t size;
    const INTERPOLATION_MODE mode;

    float alpha;
};

#endif