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

    /*VCO*/
    juce::Slider VCO_frequency_dial;
    juce::Slider VCO_LFO_ModDepth_dial;
    juce::Slider VCO_AR_ModDepth_dial;
    juce::TextButton  VCO_sync_toggleButton{};
    juce::TextButton  VCO_ARmod_toggleButton{};

    /*VCLPF*/
    juce::Slider VCLPF_cutoffFrequency_dial;
    juce::Slider VCLPF_resonance_dial;
    juce::Slider VCLPF_ModDepth_dial;
    juce::TextButton VCLPF_whiteNoise_toggleButton{};
    juce::TextButton VCLPF_LFO_toggleButton{};


    /*AREG*/
    juce::Slider AREG_attack_dial;
    juce::Slider AREG_release_dial;
    juce::TextButton  AREG_repeat_toggleButton{};
    juce::TextButton  AREG_manualGate_toggleButton{};

    /*LFO*/
    juce::Slider LFO_rate_dial;
    juce::TextButton  LFO_integrate_toggleButton{};
    juce::TextButton  LFO_derivate_toggleButton{};

    /*VCA*/
    juce::TextButton  VCA_toggleButton{};


    /*POWER*/
    juce::TextButton  PWR_toggleButton{};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyNoiseToasterAudioProcessorEditor)
};
