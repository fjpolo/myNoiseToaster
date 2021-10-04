/*
  ==============================================================================

    SynthData.cpp
    Created: 21 Sep 2021 6:31:17pm
    Author:  fjpolo

  ==============================================================================
*/

#include "SynthData.h"

SynthData::SynthData(juce::AudioProcessorValueTreeState& apvts) : apvts(apvts)
{
    /*Synth*/
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

SynthData::~SynthData()
{}

void SynthData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    /*synth*/
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, numChannels);
        }
    }
}

void SynthData::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) 
{
    /**/
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            /*update ADSR params*/
            auto& attack = *apvts.getRawParameterValue("attack");
            auto& decay = *apvts.getRawParameterValue("decay");
            auto& sustain = *apvts.getRawParameterValue("sustain");
            auto& release = *apvts.getRawParameterValue("release");
            voice->updateADSR(attack.load(), decay.load(), sustain.load(), release.load());

            /*osc*/
            auto& oscWaveChoice = *apvts.getRawParameterValue("osc1wavetype");
            voice->getOscillator().setWaveType(oscWaveChoice);
        }
    }

    /*MIDI message description*/
    for (const juce::MidiMessageMetadata metadata : midiMessages)
        if (metadata.numBytes == 3)
            juce::Logger::writeToLog("Timestamp: " + (juce::String)metadata.getMessage().getTimeStamp());

    /*Synth*/
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

