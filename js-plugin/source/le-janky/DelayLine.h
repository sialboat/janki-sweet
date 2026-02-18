
#pragma once

#ifndef DELAY_LINE_H
#define DELAY_LINE_H

#include "Buffer.h"
#include "small_math.h"
#include <algorithm>
#include <cassert>

enum class INTERPOLATION_MODE {
    NEAREST_NEIGHBORS = 0,
    LINEAR = 1,
    CUBIC = 2,
    LAGRANGE = 3,
    HERMITE = 4,
    THIRAN = 5
};

/*
    DelayLine

    Object that represents a floating point buffer that allows reading, storing, and interpolation
    between sample points. By default, six different interpoation algorithms are implemented. Samples
    are stored in a circular buffer (once we reach the end of the array, we will fold back to the
    beginning.) according to the value of writeIndex. ReadIndex isn't actually used in this rendition
    of the buffer, as the samples that are beig read are determined by the writeIndex and the delay
    (in samples) that the user wishes to read from. Some interpolation algorithms require an alpha
    value (x in [0, 1]) for computations. This value by default is 0.5f but can be changed using the
    setAlpha() function.
*/
class DelayLine
{
    public:
    DelayLine();
    DelayLine(size_t size, INTERPOLATION_MODE m = INTERPOLATION_MODE::LAGRANGE);

    size_t getBufferLength() { return size; }
    size_t getReadIndex() { return readIndex; }
    size_t getWriteIndex() { return writeIndex; }
    void setReadIndex(size_t newIndex) { readIndex = newIndex; }
    void setWriteIndex(size_t newIndex) { writeIndex = newIndex; }

    float getAlpha() { return alpha; }
    void setAlpha(float f) { alpha = f; }

    void setCapacity(size_t newCapacity);               // sets capacity to a larger length and zeros the buffer.

    float read();                                       // read at writeIndex
    float readBehind(float i);                          // read i indices behind writeIndex
    float readRaw(size_t i);                            // reads the value stored at writeIndex

    void write(float in);                               // write in at writeIndex
    void writeAhead(float in, size_t i);                // write in i indices ahead writeIndex
    void writeBehind(float in, size_t i);               // write in i indices behind writeIndex
    void writeAt(float in, int i);                   // write in at index i

    void clear() { buffer.clear(); }                    // zero the buffer with buffer.clear();
    void reset();                                       // zero the buffer iteratively.

    Buffer& getBuffer() { return buffer; }

    private:
    float interpolate(float at = 0.0f);                 // interpolateion algorithms at index at.
    float linear(float at = 0.0f);                      // linear interpolation
    float nearest_neighbors(float at = 0.0f);           // nearest neighbors interpolation
    float cubic(float at = 0.0f);                       // cubic interpol;ation
    float lagrange(float at = 0.0f);                    // lagrange interpolation
    float hermite(float at = 0.0f);                     // hermite interpolation
    float thiran(float at = 0.0f, int order = 1);           // thiran allpass interpolation
    // float thiran_1(float at = 0.0f);                 // first order thiran interpolation

    private:
    // size_t size is implicitly defined via the buffer class.
    // can be accessed using buffer.size(); but this is inefficient so
    // we are just going to cache it.
    buffer<float> buffer;
    size_t readIndex;
    size_t writeIndex;
    size_t size;
    float alpha;
    const INTERPOLATION_MODE mode;

};

#endif