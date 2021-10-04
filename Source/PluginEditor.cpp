/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
MyNoiseToasterAudioProcessorEditor::MyNoiseToasterAudioProcessorEditor (MyNoiseToasterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), noiseToaster(audioProcessor.apvts)
{
    /*NoiseToaster*/
    addAndMakeVisible(noiseToaster);

    /*PWR_toggleButton*/
    addAndMakeVisible(PWR_toggleButton);
    PWR_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    PWR_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    PWR_toggleButton.setButtonText("OFF");
    PWR_toggleButton.addListener(this);

    ///*Scope*/
    addAndMakeVisible(audioProcessor.oscilloscope);

    /*Window*/
    setSize(785, 783);
}
MyNoiseToasterAudioProcessorEditor::~MyNoiseToasterAudioProcessorEditor()
{
    
}

//==============================================================================
void MyNoiseToasterAudioProcessorEditor::paint (juce::Graphics& g)
{
    /**
    * https://docs.juce.com/master/classImageCache.html#details
    * https://forum.juce.com/t/how-to-add-a-background-image/21454
    */
    auto imageBackground = juce::ImageCache::getFromMemory(BinaryData::Background_PNG, BinaryData::Background_PNGSize);
    g.drawImageAt(imageBackground, 0, 0);
}
void MyNoiseToasterAudioProcessorEditor::resized()
{
    /*NoiseToaster*/
    noiseToaster.setBounds(0, 0, 785, 783);

    /*PWR dials*/
    const int PWR_toggleButtonRadius{ 20 };
    const int PWR_toggleButtonDiameter{ PWR_toggleButtonRadius * 2 };
    const int PWR_ToggleButtonX{ 654 };
    const int PWR_ToggleButtonY{ 654 };
    PWR_toggleButton.setBounds(PWR_ToggleButtonX - PWR_toggleButtonRadius, PWR_ToggleButtonY - PWR_toggleButtonRadius, PWR_toggleButtonDiameter, PWR_toggleButtonDiameter);

    /*Scope*/
    const int scopeWidth{ 144 };
    const int scopeHeight{ 100 };
    const int scopeX{ 658 };
    const int scopeY{ 121 };
    audioProcessor.oscilloscope.setBounds(scopeX - scopeWidth / 2, scopeY - scopeHeight / 2 + 20, scopeWidth, scopeHeight);

    
}

void MyNoiseToasterAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &PWR_toggleButton) 
    {
        if (audioProcessor.PWR_state) 
        {
            PWR_toggleButton.setButtonText("OFF");
            audioProcessor.PWR_state = false;
        }
        else
        {
            PWR_toggleButton.setButtonText("ON");
            audioProcessor.PWR_state = true;
        }
    }
}
void MyNoiseToasterAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{}