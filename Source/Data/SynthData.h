/*
  ==============================================================================

    SynthData.h
    Created: 21 Sep 2021 6:31:17pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthVoice.h"

class SynthData
{
public:
    SynthData(juce::AudioProcessorValueTreeState& apvts);
    ~SynthData();
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    /**/
    juce::AudioProcessorValueTreeState& apvts;
private:
    /*Synth*/
    juce::Synthesiser synth;

    
};