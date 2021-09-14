/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
 *
 */
class WaveVisualiser : public juce::AudioVisualiserComponent
{
public:
    WaveVisualiser() : AudioVisualiserComponent(2)
    {
        setBufferSize(1 << 7);
        setSamplesPerBlock(1 << 4);
        setColours(juce::Colours::black, juce::Colours::red);
    }
private:
};

//==============================================================================
/**
*/
class MyNoiseToasterAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener,  public juce::Slider::Listener
{
public:
    MyNoiseToasterAudioProcessorEditor (MyNoiseToasterAudioProcessor&);
    ~MyNoiseToasterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //==============================================================================
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyNoiseToasterAudioProcessor& audioProcessor;

    /*Output*/
    juce::Slider Output_volume_dial;

    /*INput*/
    juce::Slider VCLPF_inputSelect_dial;
    int VCLPF_inputSelect_state;

    /*VCO*/
    juce::Slider VCO_frequency_dial;
    juce::Slider VCO_LFO_ModDepth_dial;
    juce::Slider VCO_AR_ModDepth_dial;
    juce::TextButton  VCO_sync_toggleButton{};
    bool VCO_syncState{ false };
    juce::TextButton  VCO_ARmod_toggleButton{};
    bool VCO_ARmodState{ false };

    /*VCLPF*/
    juce::Slider VCLPF_cutoffFrequency_dial;
    juce::Slider VCLPF_resonance_dial;
    juce::Slider VCLPF_ModDepth_dial;
    juce::TextButton VCLPF_whiteNoise_toggleButton{};
    bool VCLPF_whiteNoiseState{ false };
    juce::TextButton VCLPF_LFO_toggleButton{};
    bool VCLPF_LFOState{ false };


    /*AREG*/
    juce::Slider AREG_attack_dial;
    double AREG_attackValue;
    juce::Slider AREG_release_dial;
    double AREG_releaseValue;
    juce::TextButton  AREG_repeat_toggleButton{};
    bool AREG_repeat_state{ false };
    juce::TextButton  AREG_manualGate_toggleButton{};
    bool AREG_manualGate_state{ false };

    /*LFO*/
    juce::Slider LFO_rate_dial;
    juce::TextButton  LFO_integrate_toggleButton{};
    bool LFO_integrate_state{ false };
    juce::TextButton  LFO_derivate_toggleButton{};
    bool LFO_derivate_state{ false };

    /*VCA*/
    juce::TextButton  VCA_toggleButton{};
    bool VCA_state{ false };


    /*POWER*/
    juce::TextButton  PWR_toggleButton{};
    bool PWR_state{ false };


    /**/
    double samplerate;

    /*Oscilloscope*/
    WaveVisualiser oscilloscope;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyNoiseToasterAudioProcessorEditor)
};
