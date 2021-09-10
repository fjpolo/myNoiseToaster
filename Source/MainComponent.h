#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * 
 */
class SineOscillator
{
public:
    SineOscillator() {}
    //...
    void setFrequency(float frequency, float sampleRate)
    {
        auto cyclesPerSample = frequency / sampleRate;
        angleDelta = cyclesPerSample * juce::MathConstants<float>::twoPi;
    }
    forcedinline void updateAngle() noexcept
    {
        currentAngle += angleDelta;
        if (currentAngle >= juce::MathConstants<float>::twoPi)
            currentAngle -= juce::MathConstants<float>::twoPi;
    }
    forcedinline float getNextSample() noexcept
    {
        auto currentSample = std::sin(currentAngle);
        updateAngle();
        return currentSample;
    }

private:
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
};
class SquareOscillator
{
public:
    SquareOscillator() {}
    //...
    void setFrequency(float frequency, float sampleRate)
    {
        auto cyclesPerSample = frequency / sampleRate;
        angleDelta = cyclesPerSample * juce::MathConstants<float>::twoPi;
    }
    forcedinline void updateAngle() noexcept
    {
        currentAngle += angleDelta;
        if (currentAngle >= juce::MathConstants<float>::twoPi)
            currentAngle -= juce::MathConstants<float>::twoPi;
    }
    forcedinline float getNextSample() noexcept
    {
        auto currentSample = std::sin(currentAngle);
        updateAngle();
        return currentSample;
    }

private:
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
};

//==============================================================================
/**
 *
 */
class WavetableOscillator
{
public:
    WavetableOscillator(const juce::AudioSampleBuffer& wavetableToUse)
        : wavetable(wavetableToUse)
    {
        //jassert(wavetable.getNumChannels() == 1);
        tableSize = wavetable.getNumSamples() - 1;
    }
    void setFrequency(float frequency, float sampleRate)
    {
        auto tableSizeOverSampleRate = (float)wavetable.getNumSamples() / sampleRate;
        tableDelta = frequency * tableSizeOverSampleRate;

        //auto tableSizeOverSampleRate = (float)tableSize / sampleRate;
        //tableDelta = frequency * tableSizeOverSampleRate;
    }
    forcedinline float getNextSample() noexcept
    {
        auto tableSize = (unsigned int)wavetable.getNumSamples();
        auto index0 = (unsigned int)currentIndex;              // [6]
        auto index1 = index0 == (tableSize - 1) ? (unsigned int)0 : index0 + 1;

        //auto index0 = (unsigned int)currentIndex;
        //auto index1 = index0 + 1;

        auto frac = currentIndex - (float)index0;              // [7]

        auto* table = wavetable.getReadPointer(0);             // [8]
        auto value0 = table[index0];
        auto value1 = table[index1];

        auto currentSample = value0 + frac * (value1 - value0); // [9]

        if ((currentIndex += tableDelta) > (float)tableSize)   // [10]
            currentIndex -= (float)tableSize;

        return currentSample;
    }
private:

    const juce::AudioSampleBuffer& wavetable;
    float currentIndex = 0.0f;
    float tableDelta = 0.0f;
    int tableSize;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
    public juce::Button::Listener,
    public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;


    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    /*Output*/
    juce::Slider Output_volume_dial;
    juce::dsp::Gain<float> Output_volume;
    double Output_level;

    /*VCO*/
    juce::Slider VCO_frequency_dial;
    juce::Slider VCO_LFO_ModDepth_dial;
    juce::Slider VCO_AR_ModDepth_dial;
    juce::TextButton  VCO_sync_toggleButton{};
    bool VCO_syncState{ false };
    juce::TextButton  VCO_ARmod_toggleButton{};
    bool VCO_ARmodState{ false };
    //...
    juce::Label cpuUsageLabel;
    juce::Label cpuUsageText;
    const unsigned int VCO_tableSize = 1 << 7;      // [2]
    float level = 0.0f;
    juce::AudioSampleBuffer sineTable;          // [1]
    juce::OwnedArray<WavetableOscillator> oscillators;
    double VCO_frequency;
    WavetableOscillator* VCO_osc;
    void createWavetable();
    void setFrequencies();

    /*VCLPF*/
    juce::Slider VCLPF_cutoffFrequency_dial;
    juce::Slider VCLPF_resonance_dial;
    juce::Slider VCLPF_ModDepth_dial;
    juce::Slider VCLPF_inputSelect_dial;
    juce::TextButton VCLPF_whiteNoise_toggleButton{};
    bool VCLPF_whiteNoiseState{ false };
    juce::TextButton VCLPF_LFO_toggleButton{};
    bool VCLPF_LFOState{ false };


    /*AREG*/
    juce::Slider AREG_attack_dial;
    juce::Slider AREG_release_dial;
    juce::TextButton  AREG_repeat_toggleButton{};
    bool AREG_repeat_state{ false };
    juce::TextButton  AREG_manualGate_toggleButton{};

    /*LFO*/
    juce::Slider LFO_rate_dial;
    juce::TextButton  LFO_integrate_toggleButton{};
    bool LFO_integrate_state{ false };
    juce::TextButton  LFO_derivate_toggleButton{};
    bool LFO_derivate_state{ false };
    const unsigned int LFO_tableSize = 1 << 7; 
    double LFO_frequency;
    double LFO_level;
    juce::AudioSampleBuffer LFO_waveTable;
    juce::OwnedArray<WavetableOscillator> LFO_oscillators;
    void LFO_createWavetable();
    void LFO_setFrequencies();

    /*VCA*/
    juce::TextButton  VCA_toggleButton{};
    bool VCA_state{ false };
    

    /*POWER*/
    juce::TextButton  PWR_toggleButton{};
    bool PWR_state{ false };


    /**/
    double samplerate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
