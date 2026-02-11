
// #include "DelayLine.h"

// void DelayLine::setMaximumDelayInSamples(int maxLengthInSamples)
// {
//     //verifies that the delay length is positive (so we don't set it as a negative number)
//     //this notifies if something is wrong if so
//     jassert(maxLengthInSamples > 0);

//     //allocates memory for the number of samples (we add 2 so the 1-pole smoothing can reach 5000 faster instead of plateauing)
//     int paddedLength = maxLengthInSamples + 2;

//     //don't allocate memory if the current buffer is the same or larger than needed.
//     if(bufferLength < paddedLength) {
//         // allocate memory
//         bufferLength = paddedLength;
//         buffer.reset(new float[size_t(bufferLength)]);
//     }
// }

// void DelayLine::reset()
// {
//     writeIndex = bufferLength - 1;
//     std::fill(0, bufferLength, 0);
// }

// void DelayLine::write(float input)
// {
//     jassert(bufferLength > 0);

//     writeIndex = (writeIndex + 1) & (bufferLength - 1);

//     buffer[size_t(writeIndex)] = input;
// }

// float DelayLine::read(float delayInSamples, int mode)
// {
//     switch(mode)
//     {
//         case 0: return lineaer(delayInSamples);
//         case 1: return lagrange(delayInSamples);
//         case 2: return cubic(delayInSamples);
//         case 3: return hermite(delayInSamples);
//         default: return lagrange(delayInSamples);
//     }
// }

// float DelayLine::lagrange(float)