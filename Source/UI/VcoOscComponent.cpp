/*
  ==============================================================================

    OscComponent.cpp
    Created: 21 Sep 2021 6:00:09pm
    Author:  fjpolo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VcoOscComponent.h"

//==============================================================================
VcoOscComponent::VcoOscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorID)
{
    /*frequency_dial*/
    addAndMakeVisible(frequency_dial);
    frequency_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    frequency_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    frequency_dial.setRange(0.01, 1500);
    frequency_dial.setSkewFactorFromMidPoint(750);
    frequency_dial.addListener(this);
    /*VCO_LFO_ModDepth_dial*/
    addAndMakeVisible(LFO_ModDepth_dial);
    LFO_ModDepth_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    LFO_ModDepth_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    LFO_ModDepth_dial.setRange(0, 1);
    LFO_ModDepth_dial.setValue(0);
    LFO_ModDepth_dial.addListener(this);
    /*AR_ModDepth_dial*/
    addAndMakeVisible(AR_ModDepth_dial);
    AR_ModDepth_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    AR_ModDepth_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    AR_ModDepth_dial.setRange(0, 1);
    AR_ModDepth_dial.setValue(0.0f);
    AR_ModDepth_dial.addListener(this);
    /*sync_toggleButton*/
    addAndMakeVisible(sync_toggleButton);
    sync_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    sync_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    sync_toggleButton.setButtonText("OFF");
    sync_toggleButton.addListener(this);
    /*ARmod_toggleButton*/
    addAndMakeVisible(ARmod_toggleButton);
    ARmod_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    ARmod_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    ARmod_toggleButton.setButtonText("OFF");
    ARmod_toggleButton.addListener(this);
    /*inputSelect_dial*/
    addAndMakeVisible(inputSelect_dial);
    inputSelect_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    inputSelect_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    inputSelect_dial.setRange(0, 2, 1);
    inputSelect_dial.setRotaryParameters(0, 3.14, true);
    inputSelect_dial.setValue(0);
    inputSelect_dial.addListener(this);

    //oscWaveSelectorAttachement = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    inputSelect_dialAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "osc1wavetype", inputSelect_dial);
}

VcoOscComponent::~VcoOscComponent()
{
    sync_toggleButton.removeListener(this);
    ARmod_toggleButton.removeListener(this);
}

void VcoOscComponent::paint (juce::Graphics& g)
{
    /**/
    //g.fillAll (juce::Colours::black);   
}

void VcoOscComponent::resized()
{
    //
    // oscWaveSelector.setBounds(0, 0, 90, 20);

    const int VCO_dialRadius{ 40 };
    const int VCO_dialDiameter{ VCO_dialRadius * 2 };
    const int VCO_toggleButtonRadius{ 20 };
    const int VCO_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int VCO_dialY{ 165 };
    const int VCO_dialX_frequency{ 128 };
    const int VCO_dialX_LFO_ModDepth{ 320 };
    const int VCO_dialX_AR_ModDepth{ 448 };
    const int VCO_syncToggleButtonX{ 224 };
    const int VCO_ARmodToggleButtonX{ 548 };
    frequency_dial.setBounds(VCO_dialX_frequency - VCO_dialRadius, VCO_dialY - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);
    LFO_ModDepth_dial.setBounds(VCO_dialX_LFO_ModDepth - VCO_dialRadius, VCO_dialY - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);
    AR_ModDepth_dial.setBounds(VCO_dialX_AR_ModDepth - VCO_dialRadius, VCO_dialY - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);
    sync_toggleButton.setBounds(VCO_syncToggleButtonX - VCO_toggleButtonRadius, VCO_dialY - VCO_toggleButtonRadius, VCO_toggleButtonDiameter, VCO_toggleButtonDiameter);
    ARmod_toggleButton.setBounds(VCO_ARmodToggleButtonX - VCO_toggleButtonRadius, VCO_dialY - VCO_toggleButtonRadius, VCO_toggleButtonDiameter, VCO_toggleButtonDiameter);
    inputSelect_dial.setBounds(108 - VCO_dialRadius, 314 - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);

}

void VcoOscComponent::buttonClicked(juce::Button* button)
{
        /*VCO_sync_toggleButton*/
        if (button == &sync_toggleButton)
        {
            if (!VCO_syncState) {
                VCO_syncState = true;
                sync_toggleButton.setButtonText("ON");
            }
            else {
                VCO_syncState = false;
                sync_toggleButton.setButtonText("OFF");
            }
        }
    
        /*VCO_ARmod_toggleButton*/
        if (button == &ARmod_toggleButton)
        {
            if (!VCO_ARmodState) {
                VCO_ARmodState = true;
                ARmod_toggleButton.setButtonText("ON");
            }
            else {
                VCO_ARmodState = false;
                ARmod_toggleButton.setButtonText("OFF");
            }
        }
}
void VcoOscComponent::sliderValueChanged(juce::Slider* slider)
{}