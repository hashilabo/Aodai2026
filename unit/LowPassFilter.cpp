/** 
 * LowPassFilter.cpp
 */
#include "LowPassFilter.h"

namespace {
    constexpr double TWO_PI = 6.283185307179586;
}

LowPassFilter::LowPassFilter(float cutoffFreqHz, float sampleTimeSec)
    : mAlpha(0.0f), mOutput(0.0f), mInitialized(false)
{
    // RC = 1 / (2*pi*fc),  alpha = dt / (RC + dt)
    const float rc = 1.0 / (TWO_PI * cutoffFreqHz);
    mAlpha = sampleTimeSec / (rc + sampleTimeSec);
}

float LowPassFilter::update(float input)
{
    if (!mInitialized) {
        // 起動直後にmOutput=0からの過渡応答が出るのを防ぐ
        mOutput = input;
        mInitialized = true;
        return mOutput;
    }

    mOutput = mAlpha * input + (1.0 - mAlpha) * mOutput;
    return mOutput;
}

void LowPassFilter::reset(float initialValue)
{
    mOutput = initialValue;
    mInitialized = true;
}
