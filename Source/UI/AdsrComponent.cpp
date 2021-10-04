/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 21 Sep 2021 4:35:53pm
    Author:  fjpolo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    /*attack_dial*/
    addAndMakeVisible(attack_dial);
    attack_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attack_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    attack_dial.setRange(0, 0.5);
    attack_dial.addListener(this);
    attack_dial.setValue(0);
    /*release_dial*/
    addAndMakeVisible(release_dial);
    release_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    release_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    release_dial.setRange(0, 0.5);
    release_dial.addListener(this);
    release_dial.setValue(0);
    /*manualGate_toggleButton*/
    addAndMakeVisible(manualGate_toggleButton);
    manualGate_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    manualGate_toggleButton.addListener(this);
    /*repeat_toggleButton*/
    addAndMakeVisible(repeat_toggleButton);
    repeat_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    repeat_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    repeat_toggleButton.setButtonText("M");
    repeat_toggleButton.addListener(this);
   

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    /**/
    // g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
    /*Sliders*/
    const int AREG_dialRadius{ 40 };
    const int AREG_dialDiameter{ AREG_dialRadius * 2 };
    const int AREG_toggleButtonRadius{ 20 };
    const int AREG_toggleButtonDiameter{ AREG_toggleButtonRadius * 2 };
    const int AREG_dialY{ 552 };
    const int AREG_dialX_attack{ 128 };
    const int AREG_dialX_release{ 268 };
    attack_dial.setBounds(AREG_dialX_attack - AREG_dialRadius, AREG_dialY - AREG_dialRadius, AREG_dialDiameter, AREG_dialDiameter);
    release_dial.setBounds(AREG_dialX_release - AREG_dialRadius, AREG_dialY - AREG_dialRadius, AREG_dialDiameter, AREG_dialDiameter);
    repeat_toggleButton.setBounds(206 - AREG_toggleButtonRadius, 680 - AREG_toggleButtonRadius, AREG_toggleButtonDiameter, AREG_toggleButtonDiameter);
    manualGate_toggleButton.setBounds(112 - AREG_toggleButtonRadius, 680 - AREG_toggleButtonRadius, AREG_toggleButtonDiameter, AREG_toggleButtonDiameter);
 }

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    ///*slider*/
    //slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    //slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    //slider.setRange(0, 1);
    //addAndMakeVisible(slider);
}

void AdsrComponent::buttonClicked(juce::Button* button)
{}
void AdsrComponent::sliderValueChanged(juce::Slider* slider)
{}