/*
  ==============================================================================

    dsp.h
    Created: 20 May 2025 3:27:56pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once

namespace mldsp
{
namespace dsp
{

// ==============================================================================

struct Index
{
    Index() = default;
    ~Index() {};
        
    /// -----------------------------

    inline void set (const size_t targetIndex,
                     const size_t bounds = 0)
    {
        this->pos = targetIndex % bounds;
    }
    
    inline size_t get() { return pos; }
    
    inline void incrementAndWrap (const int amt,
                                  const size_t bounds)
    {
        pos = (pos + amt) % bounds;
    }
    
    /// -----------------------------
    
    size_t pos = 0;
};

class Delay
{
public:
    
    Delay(const size_t maxDelayInSamples) : maxBufferSize(maxDelayInSamples), buffer(new float[maxDelayInSamples+1]()), delayInSamples(maxDelayInSamples) {}
    ~Delay() { delete[] buffer; }
    
    /// -----------------------------
    
    inline void setup (const float targetDelayInSamples) noexcept
    {
        this->delayInSamples = targetDelayInSamples;
        isFractional = true;
    }
    
    inline void setup (const int targetDelayInSamples) noexcept
    {
        this->delayInSamples = targetDelayInSamples;
        isFractional = false;
    }
        
    /// -----------------------------

    inline void process (juce::AudioBuffer<float> &buffer, int channel)
    {
        auto* ptr = buffer.getWritePointer (channel);
        for (size_t n = 0; n < buffer.getNumSamples(); ++n)
            ptr[n] = push (ptr[n]);
    }
    
private:
    
    inline float push (const float x)
    {
        // Read
        rIdx.set (wIdx.get() - delayInSamples + maxBufferSize, maxBufferSize);
        float y = buffer[rIdx.get()];
        
        // Write
        buffer[wIdx.get()] = x;
        wIdx.incrementAndWrap (1, maxBufferSize);
        
        return y;
    }

    /// -----------------------------

    size_t maxBufferSize;
    float* buffer;

    float delayInSamples;
    Index rIdx, wIdx;

    bool isFractional;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Delay);
};

// ==============================================================================

}; // namespace dsp
}; // namespace mldsp
