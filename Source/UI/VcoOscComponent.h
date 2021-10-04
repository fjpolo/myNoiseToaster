/*
  ==============================================================================

    OscComponent.h
    Created: 21 Sep 2021 6:00:09pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VcoOscComponent  : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener
{
public:
    VcoOscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID);
    ~VcoOscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    /**/
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;


private:
    juce::Slider frequency_dial;
    juce::Slider LFO_ModDepth_dial;
    juce::Slider AR_ModDepth_dial;
    juce::TextButton  sync_toggleButton{};
    juce::TextButton  ARmod_toggleButton{};
    juce::Slider inputSelect_dial;

    bool VCO_syncState{ false };
    bool VCO_ARmodState{ false }; 

    juce::ComboBox oscWaveSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachement;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputSelect_dialAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VcoOscComponent)
};
