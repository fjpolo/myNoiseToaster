/*
  ==============================================================================

    SynthComponent.h
    Created: 21 Sep 2021 6:30:32pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VcoOscComponent.h"
#include "AdsrComponent.h"

//==============================================================================
/*
*/
class SynthComponent  : public juce::Component
{
public:
    SynthComponent(juce::AudioProcessorValueTreeState& apvts);
    ~SynthComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /*Param tree*/
    juce::AudioProcessorValueTreeState& apvts;


private:
    ///*Output*/
    //juce::Slider Output_volume_dial;

    ///*Input*/
    //juce::Slider VCLPF_inputSelect_dial;

    ///*VCO*/
    //juce::Slider VCO_frequency_dial;
    //juce::Slider VCO_LFO_ModDepth_dial;
    //juce::Slider VCO_AR_ModDepth_dial;
    //juce::TextButton  VCO_sync_toggleButton{};
    //juce::TextButton  VCO_ARmod_toggleButton{};

    ///*VCLPF*/
    //juce::Slider VCLPF_cutoffFrequency_dial;
    //juce::Slider VCLPF_resonance_dial;
    //juce::Slider VCLPF_ModDepth_dial;
    //juce::TextButton VCLPF_whiteNoise_toggleButton{};
    //juce::TextButton VCLPF_LFO_toggleButton{};


    ///*AREG*/
    //juce::Slider AREG_attack_dial;
    //juce::Slider AREG_release_dial;
    //juce::TextButton  AREG_repeat_toggleButton{};
    //juce::TextButton  AREG_manualGate_toggleButton{};

    ///*LFO*/
    //juce::Slider LFO_rate_dial;
    //juce::TextButton  LFO_integrate_toggleButton{};
    //juce::TextButton  LFO_derivate_toggleButton{};

    ///*VCA*/
    //juce::TextButton  VCA_toggleButton{};


    ///*POWER*/
    //juce::TextButton  PWR_toggleButton{};

    /*VCO*/
    VcoOscComponent vcoComp;

    /*AREG (AREG)*/
    AdsrComponent adsr;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthComponent)
};
