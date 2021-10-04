/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Data/SynthData.h"

/**/
const auto BUFFER_SIZE = 1 << 7;
const auto OSC_BLOCK_SIZE = 1 << 4;
const auto MAX_CUTOFF_FREQ = 100000.0f;

enum class WaveType {
    Sawtooh = 0,
    Off,
    Square
};

//==============================================================================
/**
 *
 */
class WaveVisualiser : public juce::AudioVisualiserComponent
{
public:
    WaveVisualiser() : AudioVisualiserComponent(2)
    {
        setBufferSize(BUFFER_SIZE);
        setSamplesPerBlock(OSC_BLOCK_SIZE);
        setColours(juce::Colours::black, juce::Colours::red);
    }
private:
};

//==============================================================================
/**
*/
class MyNoiseToasterAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MyNoiseToasterAudioProcessor();
    ~MyNoiseToasterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    /*Parameters*/
    juce::dsp::ProcessSpec spec; 
    double VCO_frequency{ 220.0f };
    double LFO_frequency{ 3.0f };
    WaveType VCO_waveType;
    double AREG_attackValue;
    double AREG_releaseValue;
    double Output_gain{0.25f};
    double VCLPF_cutoffFrequency{25000.0f};
    double VCLPF_resonance{0.4f};

    /*Button states*/
    bool PWR_state{ false };
    bool VCO_syncState{ false };
    bool VCO_ARmodState{ false };
    bool VCLPF_whiteNoiseState{ false };
    bool VCLPF_LFOState{ false };
    bool AREG_repeat_state{ false };
    bool AREG_manualGate_state{ false };
    bool LFO_integrate_state{ false };
    bool LFO_derivate_state{ false };
    bool VCA_state{ false };

    /*Processor indices - top-down order*/
    enum
    {
        VCO_oscIndex,
        VCLPF_filterIndex,
        Output_gainIndex
    };

    /*Processing chain*/
    juce::dsp::ProcessorChain< 
                                juce::dsp::Oscillator<float>, 
                                juce::dsp::LadderFilter<float>,
                                juce::dsp::Gain<float> 
                             > processorChain;

    /*LFO*/
    juce::dsp::AudioBlock<float> tempBlock; 
    static constexpr size_t lfoUpdateRate = 100;
    size_t lfoUpdateCounter = lfoUpdateRate;
    juce::dsp::Oscillator<float> lfo;

    /*Oscilloscope*/
    WaveVisualiser oscilloscope;

    void VCO_changeWave();
    void LFO_changeWave();
    void Output_setGain();
    void VCO_setFrequency();
    void LFO_setFrequency();
    void VCLPF_setFrequency();
    void VCLPF_setResonance();

    /*Param tree*/
    juce::AudioProcessorValueTreeState apvts;

private:
    //==============================================================================

    /*SynthData*/
    SynthData noiseToasterData;
    /**/
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyNoiseToasterAudioProcessor)
};
