/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/SynthComponent.h"

//==============================================================================
/**
*/
class MyNoiseToasterAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener, public juce::Slider::Listener
{
public:
    MyNoiseToasterAudioProcessorEditor (MyNoiseToasterAudioProcessor&);
    ~MyNoiseToasterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    /**/
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyNoiseToasterAudioProcessor& audioProcessor;

    /*POWER*/
    juce::TextButton  PWR_toggleButton;

    /*Noise Toaster*/
    SynthComponent noiseToaster;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyNoiseToasterAudioProcessorEditor)
};
