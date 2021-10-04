/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Sep 2021 3:30:08pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h> 
#include "SynthSound.h"
#include "AdsrData.h"
#include "VcoOscData.h"

/**
* \class SynthVoice
*
**/
class SynthVoice : public juce::SynthesiserVoice 
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    VcoOscData& getOscillator() { return osc; };
private:
    //==============================================================================
    
    /*synthBuffer*/
    juce::AudioBuffer<float> synthBuffer;

    /*Oscillator*/
    VcoOscData osc;
    // juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x); } };    // Sine
    // juce::dsp::Oscillator<float> osc{ [](float x) { return (x / juce::MathConstants<float>::pi); } };    // Sawtooth
    // juce::dsp::Oscillator<float> osc{ [](float x) { return ((x < 0.0f) ? (-1.0f) : (1.0f)); }, 256 };   // Square
    
    /*Gain*/
    juce::dsp::Gain<float> gain;

    /**/
    AdsrData adsr;
    

    /*isPrepared*/
    bool isPrepared{ false };
};