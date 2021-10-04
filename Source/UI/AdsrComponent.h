/*
  ==============================================================================

    AdsrComponent.h
    Created: 21 Sep 2021 4:35:53pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    /*setSliderParams*/
    void setSliderParams(juce::Slider& slider);
    /**/
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    /*Attachmentes*/
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attack_dialAttachment;
    std::unique_ptr<SliderAttachment> release_dialAttachment;
    /*Sliders*/
    juce::Slider attack_dial;
    juce::Slider release_dial;
    juce::TextButton  repeat_toggleButton{};
    juce::TextButton  manualGate_toggleButton{};
    /**/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
