/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Sep 2021 3:30:08pm
    Author:  fjpolo

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
    /*SynthoSound correctly casting*/
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    /*OSC*/
    osc.setWaveFrequency(midiNoteNumber);

    /*ADSR*/
    adsr.noteOn();
}
void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
    /*ADSR*/
    adsr.noteOff();

    /**/
    if (!allowTailOff || !adsr.isActive()) 
    {
        clearCurrentNote();
    }

}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{
}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels)
{
    /*ADSR*/
    adsr.setSampleRate(sampleRate);

    /*Specifications*/
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numOutputChannels;
    osc.prepareToPlay(spec);   
    
    /*Gain*/
    gain.prepare(spec);
    gain.setGainLinear(0.25f);

    /*isPrepared*/
    isPrepared = true;
}
void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsr.update(attack, decay, sustain, release);
}


void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    /*Assert*/
    jassert(isPrepared);

    /*!isVoiceActive*/
    if (!isVoiceActive()) 
    {
        return;
    }

    /*synthBuffer*/
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    /*AudioBlock*/
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    /*Process*/
    osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    /*ADSR*/
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    /**/
    //if (startSample != 0)
    //{
    //    jassertfalse;  
    //}

    /**/
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) 
        {
            clearCurrentNote();
        }
    }

}