/*
  ==============================================================================

    SynthSound.h
    Created: 15 Sep 2021 3:30:14pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/**
* \class SynthSound
*
**/
class SynthSound : public juce::SynthesiserSound 
{
public:
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }
    bool appliesToChannel(int midiChannel) override
    {
        return true;
    }
private:
};