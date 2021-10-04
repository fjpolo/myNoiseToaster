/*
  ==============================================================================

    OscData.h
    Created: 21 Sep 2021 5:22:33pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VcoOscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setWaveFrequency(const int midiNoteNumber);
    void setWaveType(const int choice);
private:
};