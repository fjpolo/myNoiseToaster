/*
  ==============================================================================

    AdsrData.cpp
    Created: 21 Sep 2021 4:36:03pm
    Author:  fjpolo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrData.h"

//==============================================================================
void AdsrData::update(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    setParameters(adsrParams);
}
