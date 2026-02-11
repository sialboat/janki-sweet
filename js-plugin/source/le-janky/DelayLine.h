
// #pragma once

// #ifndef DELAY_LINE_H
// #define DELAY_LINE_H

// #include <memory>
// #include <algorithm>

// class DelayLine
// {
//     public:
//     void setMaximumDelayInSamples(int maxLengthInSamples);
//     void reset() noexcept;
//     void write(float input) noexcept);
//     float read(float delayInSamples, int mode = 1);

//     float lagrange(float delayInSamples) const noexcept;
//     float cubic(float delayInSamples) const noexcept;
//     float hermite(float delayInSamples) const noexcept;
//     float linear(float delayInSamples) const noexcept;
    
//     int getBufferLength() const noexcept { return bufferLength; }
//     private:
//     std::unique_ptr<float[]> buffer;
//     int bufferLength = 0;
//     int writeIndex = 0;
// };

// #endif