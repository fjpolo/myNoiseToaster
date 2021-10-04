/*
  ==============================================================================

    OscData.cpp
    Created: 21 Sep 2021 5:22:33pm
    Author:  fjpolo

  ==============================================================================
*/

#include "VcoOscData.h"

void VcoOscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
}

void VcoOscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void VcoOscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void VcoOscData::setWaveType(const int choice)
{
    // return std::sin(x);                              // Sine
    // return (x / juce::MathConstants<float>::pi);     // Sawtooth
    // return ((x < 0.0f) ? (-1.0f) : (1.0f));          // Square

    /*Switch input*/
    switch (choice)
    {
        case 0:
        {
            // Saw
            // juce::dsp::Oscillator<float> osc{ [](float x) { return (x / juce::MathConstants<float>::pi); } };    // Sawtooth
            initialise([](float x) { return (x / juce::MathConstants<float>::pi); });
            break;
        }
        case 2:
        {
            // Square
            // juce::dsp::Oscillator<float> osc{ [](float x) { return ((x < 0.0f) ? (-1.0f) : (1.0f)); }, 256 };   // Square
            initialise([](float x) { return ((x < 0.0f) ? (-1.0f) : (1.0f)); });
            break;
        }
        case 1:
        default:
        {
            initialise([](float x) { return 0.0f; });
            break;
        }
        
    }

}

