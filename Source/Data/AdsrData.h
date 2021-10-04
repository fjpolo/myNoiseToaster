/*
  ==============================================================================

    AdsrData.h
    Created: 21 Sep 2021 4:36:03pm
    Author:  fjpolo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrData  : public juce::ADSR
{
public:
    /*ADSR*/
    juce::ADSR::Parameters adsrParams; 
    void AdsrData::update(const float attack, const float decay, const float sustain, const float release);
private:

};
