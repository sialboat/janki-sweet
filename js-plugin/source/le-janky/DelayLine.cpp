
#include "DelayLine.h"

DelayLine::DelayLine() : buffer(64), readIndex(0), writeIndex(0), size(buffer.size()),
    mode(INTERPOLATION_MODE::LAGRANGE) {}

DelayLine::DelayLine(size_t _size) : buffer(_size), readIndex(0), writeIndex(0), 
    size(buffer.size()), mode(m) {}

void DelayLine::setCapacity(size_t newSize)
{
    jassert(newSize > 0);

    size_t paddedLength = newSize + 2;

    if(buffer.size() < paddedLength) {
        buffer.resize(newSize);
        size = newSize;
    }
}

float DelayLine::read()
{

}

// float DelayLine::readAhead(float i)
// {
//     // this may not technically be possible
// }

float DelayLine::readBehind(float i)
{

}

float DelayLine::readAt(float i)
{

}


void DelayLine::write(float in)
{
    writeAt(in, writeIndex++);
    // jassert(buffer.size() > 0);
    // buffer[writeIndex] = in;
    // writeIndex = (writeIndex + 1) % buffer.size();
}

void DelayLine::writeAhead(float in, size_t i)
{
    writeAt(in, writeIndex + i);
    // jassert(buffer.size() > 0);
    // float newWrite = (writeIndex + i) % buffer.size();
    // buffer[newWrite] = in;
    // writeIndex = newWrite;
}

void DelayLine::writeBehind(float in, size_t i)
{
    writeAt(in, writeIndex - i);
}

void DelayLine::writeAt(float in, int i)
{
    jassert(buffer.size() > 0);

    writeIndex = i % buffer.size();
    buffer[writeIndex] = in;
}

void DelayLine::reset()
{
    writeIndex = buffer.size() - 1;
    for(size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = 0.0f;
    }
}


float DelayLine::interpolate(float at = 0.0f)
{
    switch(mode)
    {
        case NEAREST_NEIGHBORS:     return nearest_neighbors(at);
        case LINEAR:                return linear(at);
        case CUBIC:                 return cubic(at);
        case LAGRANGE:              return lagrange(at);
        case HERMITE:               return hermite(at);
        case THIRAN:                return thiran(at);
        default:                    return lagrange(at); // we shouldn't get here
    }
}

// replace if with while possibly to accomodate for large shifts
// but that's probably not going to happen with respect to index
// modifications


float DelayLine::nearest_neighbors(float at = 0.0f)
{
    int index = writeIndex - (int)std::round(at);
    if(index < 0) index += size; // this is faster than modulo
    return buffer[size_t(index)];
}

float DelayLine::linear(float delay = 0.0f)
{
    int base = static_cast<int>(delay);
    float frac = delay - static_cast<float>(base);

    size_t index1 = writeIndex + base;
    if(index1 < 0) index1 += size;
    size_t index2 = index1 + 1;
    if(index2 > size) index2 -= size;

    return (1 - frac) * buffer[index1] + (frac) * buffer[index2];
}

float DelayLine::cubic(float delay = 0.0f)
{
    int base = static_cast<int>(delay);
    float frac = at - static_cast<float>(base);
    float frac2 = frac * frac;
    float frac3 = frac2 * frac;

    int readIndices[4];
    float samples[4];
    for(size_t i = 0; i < 4; i++) {
        readIndices[i] = writeIndex - base + i - 1;
        if(readIndices[i] < 0) readIndices[i] += size;
        // if(readIndices[i] < 0)
        //     readIndices[i] += size;
        // if(readIndices[i] >= size)
        //     readIndices[i] -= size;
        
        samples[i] = buffer[static_cast<size_t>(readIndices[i])];
    }

    float a0 = samples[3] - samples[2] - samples[0] + samples[1];
    float a1 = samples[0] - samples[1] - a0;
    float a2 = samples[2] - samples[0];
    float a3 = samples[1];

    return a0 * frac3 + a1 * frac2 + a2 * frac + a3;
}

/*
   Barycentric Lagrange implementation.
   Lagrange interpolation is the smallest degree polynomial to pass through data points. 
   We can calculate x-coordinate positions by multiplying a their basis value with the y-value and 
   summing each of these components. We use the optimized Barycentric form which can apparently be
   rewritten as

   ( sum ((w_j) / (x - x_j) * p_j)  ) / ( sum( (w_j / (x - x)j) ) )

   where x is the distance from point 1 to point 2
   x_j is the time value of the jth sample
   p_j is the value of the jth sample
   w_j is the jth weight value associated with each sample.

   Since this is done in realtime with the latest 2 samples, we know
   x0 = 0 (index of the sample we just collected)
   x1 = -1 (index of the sample before x0)
   x2 = -2 (index of the sample before x1)

   Similarly, we can compute weights w0, w1, w2 because our sample indices are constant. We use
   Pi_(j != m) 1 / (x_j - x_m)

   to get
   w0 = 1 / (0 - 1)(0 - 2) = 1/2 = 0.5f
   w1 = 1 / (1 - 0)(1 - 2) = -1 = -1.0f
   w2 = 1 / (2 - 0)(2 - 1) = 1/2 = 0.5f

   All of this precomputation is done so we can achieve a performance of O(k) operations for the kth degree polynomial.
   Since we use a cubic polynomial, this is incredibly efficient.

   Referred to the "Barycentric Form" section of the Lagrange Polynomial Wikipedia Page
   https://en.wikipedia.org/wiki/Lagrange_polynomial
  */
float DelayLine::lagrange(float delay = 0.0f)
{
    float w0, w1, w2;
    float x0 = 0.0f, x1 = -1.0f, x2 = -2.0f;

    // calculate weights
    w0 = 1 / ((x0 - x1) * (x0 - x2));
    w1 = 1 / ((x1 - x0) * (x1 - x2));
    w2 = 1 / ((x2 - x0) * (x2 - x1));

    // calculate indices
    size_t i0 = writeIndex - delay;
    size_t i1 = i0 - 1;
    size_t i2 = i0 - 2;
    if(i0 < 0) i0 += size;
    if(i1 < 0) i1 += size;
    if(i2 < 0) i2 += size;

    // compute c1 and c2
    c0 = w0 / (alpha - x0);
    c1 = w1 / (alpha - x1);
    c2 = w2 / (alpha - x2);

    // compute subcomponents
    float numerator = (c0 * buffer[i0]) + (c1 * buffer[i1]) + (c2 * buffer[i2]);
    float denominator = c0 + c1 + c2;

    return numerator / denominator;
}

/*
    Hermite implementation (Cubic Hermite Spline), a generalization of lagrange interpolation
    It generalizes Lagrange by including the derivatives of p0, p1, and p2 alongside the values p0, p1, p2.
    As a result, it makes for a really good real-time interpolation for real-time computation.
    Found initially in a section of TAP's "Beginner Audio Plugin book" or whatever it was called.
    We implement the P(t) interpolation equation across a single unit interval [0, 1] in real time by replacing t for alpha

    P(t) = (2t^3 - 3t^2 + 1)p_0 + (t^3 - 2t^2 + t)m_0 + (-2t^3 + 3t^2)p_1 + (t^3 - t^2)m_1

    Referred to the "Interpolation on a single Unit Interval [0, 1]" section for this implementation on Wikipedia.
    https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Representations
  */
float DelayLine::hermite(float at = 0.0f)
{
    // pre-compute power values of alpha
    float a2 = alpha * alpha;
    float a3 = alpha * alpha * alpha;

    // pre-compute index values
    size_t i0 = writeIndex;
    size_t i1 = i0 - 1;
    size_t i2 = i0 - 2;
    size_t i3 = i0 - 3;
    if(i1 < 0) i1 += size;
    if(i2 < 0) i2 += size;
    if(i3 < 0) i3 += size;

    // calculate indices and m0 values
    // m0 = (3b[0] - 4b[-1] + b[-2]) / (2)
    // m1 = (3b[1] - 4b[0] + b[-1]) / (2)
    float m0 = 0.5 * ( (3 * buffer[i0]) - (4 * buffer[i1]) + buffer[i2] );
    float m1 = 0.5 * ( (3 * buffer[i1]) - (4 * buffer[i0]) + buffer[i1] );
    float p0 = buffer[i1];
    float p1 = buffer[i0];
    // compute subcomponents of p(t)
    float c0 = ( (2 * a3) - (3 * a2) + 1) * p0;
    float c1 = ( a3 - (2 * a2) + alpha ) * m0;
    float c2 = ( (-2 * a3) + (3 * a2) ) * p1;
    float c3 = ( (a3 + a2) ) * m1;

    return c0 + c1 + c2 + c3;
}

/*
    https://ccrma.stanford.edu/~jos/pasp/Thiran_Allpass_Interpolation_Matlab.html
*/
float DelayLine::thiran(float delay = 0.0f, int order)
{
    auto A = std::make_unique<float[]>(order);
    std::fill(A.get(), A.get() + order, 0.0f);
    for(size_t i = 0; i < order; i++) {
        float A_k = 1.0f;
        for(size_t j = 0; j < order; j++) {
            A_k = A_k * (delay - order + j) / (delay - order + i + j);
        }
        A[i] = std::pow(-1, i) * binom(order, i) * A_k;
    }
    return A[order];
}

// float DelayLine::thiran_1(float delay = 0.0f, float& prevOutput, float& prevInput)
// {
//     // coeff * x[n] - y[n - 1] + x[n - 1]
//     // input, previous input, previous output
//     // input: buffer[writeIndex]
//     // previous input: buffer[writeIndex - 1]
//     // previous output: initially 0
//     float frac = delay - std::floor(delay);
//     if(frac < 0) frac += size;

    
//     prevInput = buffer[(writeIndex - 1 + size) % size];
//     float coeff = (1.0f - frac) / (1.0f + frac);
//     float output = coeff * (buffer[writeIndex] - prevOutput) + prevInput;
//     prevOutput = output;
//     return output;
// }