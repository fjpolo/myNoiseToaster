#include "MainComponent.h"
#include "BinaryData.h"
#include <math.h>

//==============================================================================
MainComponent::MainComponent()
{
    /*** Outuput ***/
    addAndMakeVisible(Output_volume_dial);
    Output_volume_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    Output_volume_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    Output_volume_dial.setRange(0, 1);

    /*** VCO dials ***/

    /*VCO_frequency_dial*/
    addAndMakeVisible(VCO_frequency_dial);
    VCO_frequency_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCO_frequency_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCO_frequency_dial.setRange(0.01, 1500);
    VCO_frequency_dial.addListener(this);
    VCO_frequency_dial.setValue(220);
    /*VCO_LFO_ModDepth_dial*/
    addAndMakeVisible(VCO_LFO_ModDepth_dial);
    VCO_LFO_ModDepth_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCO_LFO_ModDepth_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCO_LFO_ModDepth_dial.setRange(0, 1);
    VCO_LFO_ModDepth_dial.addListener(this);
    VCO_LFO_ModDepth_dial.setValue(0);
    /*VCO_AR_ModDepth_dial*/
    addAndMakeVisible(VCO_AR_ModDepth_dial);
    VCO_AR_ModDepth_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCO_AR_ModDepth_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCO_AR_ModDepth_dial.setRange(0, 1);
    /*VCO_sync_toggleButton*/
    addAndMakeVisible(VCO_sync_toggleButton);
    VCO_sync_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!VCO_syncState) {
        VCO_sync_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        VCO_sync_toggleButton.setButtonText("OFF");
    }
    else {
        VCO_sync_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        VCO_sync_toggleButton.setButtonText("ON");
    }
    VCO_sync_toggleButton.addListener(this);
    /*VCO_ARmod_toggleButton*/
    addAndMakeVisible(VCO_ARmod_toggleButton);
    VCO_ARmod_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!VCO_ARmodState) {
        VCO_ARmod_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        VCO_ARmod_toggleButton.setButtonText("OFF");
    }
    else {
        VCO_ARmod_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        VCO_ARmod_toggleButton.setButtonText("ON");
    }
    VCO_ARmod_toggleButton.addListener(this);


    /*** VCLPF ***/

    /*VCLPF_cutoffFrequency_dial*/
    addAndMakeVisible(VCLPF_cutoffFrequency_dial);
    VCLPF_cutoffFrequency_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCLPF_cutoffFrequency_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCLPF_cutoffFrequency_dial.setRange(0, 10);
    /*VCLPF_resonance_dial*/
    addAndMakeVisible(VCLPF_resonance_dial);
    VCLPF_resonance_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCLPF_resonance_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCLPF_resonance_dial.setRange(0, 10);
    /*VCLPF_ModDepth_dial*/
    addAndMakeVisible(VCLPF_ModDepth_dial);
    VCLPF_ModDepth_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCLPF_ModDepth_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCLPF_ModDepth_dial.setRange(0, 10);
    /*VCLPF_inputSelect_dial*/
    addAndMakeVisible(VCLPF_inputSelect_dial);
    VCLPF_inputSelect_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    VCLPF_inputSelect_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    VCLPF_inputSelect_dial.setRange(0, 2, 1);
    VCLPF_inputSelect_dial.setRotaryParameters(0, 3.14, true);
    /*VCLPF_whiteNoise_toggleButton*/
    addAndMakeVisible(VCLPF_whiteNoise_toggleButton);
    VCLPF_whiteNoise_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!VCLPF_whiteNoiseState) {
        VCLPF_whiteNoise_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        VCLPF_whiteNoise_toggleButton.setButtonText("OFF");
    }
    else {
        VCLPF_whiteNoise_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        VCLPF_whiteNoise_toggleButton.setButtonText("ON");
    }
    VCLPF_whiteNoise_toggleButton.addListener(this);
    /*VCLPF_LFO_toggleButton*/
    addAndMakeVisible(VCLPF_LFO_toggleButton);
    VCLPF_LFO_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!VCLPF_whiteNoiseState) {
        VCLPF_LFO_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        VCLPF_LFO_toggleButton.setButtonText("AR");
    }
    else {
        VCLPF_LFO_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        VCLPF_LFO_toggleButton.setButtonText("LFO");
    }
    VCLPF_LFO_toggleButton.addListener(this);

    /*** AREG ***/
    addAndMakeVisible(AREG_attack_dial);
    AREG_attack_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    AREG_attack_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    AREG_attack_dial.setRange(0, 10);
    addAndMakeVisible(AREG_release_dial);
    AREG_release_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    AREG_release_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    AREG_release_dial.setRange(0, 10);
    /*AREG_manualGate_toggleButton*/
    addAndMakeVisible(AREG_manualGate_toggleButton);
    AREG_manualGate_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    AREG_manualGate_toggleButton.addListener(this);
    /*AREG_repeat_toggleButton*/
    addAndMakeVisible(AREG_repeat_toggleButton);
    AREG_repeat_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!AREG_repeat_state) {
        AREG_repeat_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        AREG_repeat_toggleButton.setButtonText("M");
    }
    else {
        AREG_repeat_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        AREG_repeat_toggleButton.setButtonText("R");
    }
    AREG_repeat_toggleButton.addListener(this);


    /*** LFO ***/


    /*LFO_rate_dial*/
    addAndMakeVisible(LFO_rate_dial);
    LFO_rate_dial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    LFO_rate_dial.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    LFO_rate_dial.setRange(1, 200);
    LFO_rate_dial.addListener(this);
    LFO_rate_dial.setValue(10);

    /*LFO_integrate_toggleButton*/
    addAndMakeVisible(LFO_integrate_toggleButton);
    LFO_integrate_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!LFO_integrate_state) {
        LFO_integrate_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        LFO_integrate_toggleButton.setButtonText("OFF");
    }
    else {
        LFO_integrate_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        LFO_integrate_toggleButton.setButtonText("I");
    }
    LFO_integrate_toggleButton.addListener(this);
    /*LFO_derivate_toggleButton*/
    addAndMakeVisible(LFO_derivate_toggleButton);
    LFO_derivate_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!LFO_derivate_state) {
        LFO_derivate_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        LFO_derivate_toggleButton.setButtonText("OFF");
    }
    else {
        LFO_derivate_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        LFO_derivate_toggleButton.setButtonText("D");
    }
    LFO_derivate_toggleButton.addListener(this);


    /*** VCA ***/

    /*VCA_toggleButton*/
    addAndMakeVisible(VCA_toggleButton);
    VCA_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!VCA_state) {
        VCA_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        VCA_toggleButton.setButtonText("OFF");
    }
    else {
        VCA_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        VCA_toggleButton.setButtonText("ON");
    }
    VCA_toggleButton.addListener(this);

    /*** PWR ***/

    /*PWR_toggleButton*/
    addAndMakeVisible(PWR_toggleButton);
    PWR_toggleButton.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    if (!PWR_state) {
        PWR_toggleButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        PWR_toggleButton.setButtonText("OFF");
    }
    else {
        PWR_toggleButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        PWR_toggleButton.setButtonText("ON");
    }

    PWR_toggleButton.addListener(this);


    /*Window*/
    setSize(785, 783);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }


    /**/
    cpuUsageLabel.setText("CPU Usage", juce::dontSendNotification);
    cpuUsageText.setJustificationType(juce::Justification::right);
    addAndMakeVisible(cpuUsageLabel);
    addAndMakeVisible(cpuUsageText);
    VCO_createWavetable();
    LFO_createWavetable();
    setAudioChannels(0, 2); // no inputs, two outputs
    //startTimer(50);
    VCO_frequency = 220;
    LFO_frequency = 10;
    LFO_level = 0;
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    /*Remove Listeners*/
    VCO_sync_toggleButton.removeListener(this);
    VCO_ARmod_toggleButton.removeListener(this);
    VCLPF_whiteNoise_toggleButton.removeListener(this);
    VCLPF_LFO_toggleButton.removeListener(this);
    AREG_repeat_toggleButton.removeListener(this);
    AREG_manualGate_toggleButton.removeListener(this);
    LFO_integrate_toggleButton.removeListener(this);
    LFO_derivate_toggleButton.removeListener(this);
    VCA_toggleButton.removeListener(this);
    PWR_toggleButton.removeListener(this);
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{    
    
    samplerate = sampleRate;
    /**/
    auto* oscillator1 = new WavetableOscillator(sawtoothTable);
    auto* oscillator2 = new WavetableOscillator(LFO_waveTable);
    oscillator1->setFrequency((float)220, (float)sampleRate);
    oscillator2->setFrequency((float)55, (float)sampleRate);
    /*VCO*/
    oscillators.add(oscillator1);
    /*LFO*/
    LFO_oscillators.add(oscillator2);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    /**/
    auto* leftBuffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample); // [7]
    auto* rightBuffer = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    bufferToFill.clearActiveBufferRegion();
    
    //for (auto oscillatorIndex = 0; oscillatorIndex < oscillators.size(); ++oscillatorIndex)
    //{
    //    auto* oscillator = oscillators.getUnchecked(oscillatorIndex);                      // [8]

    //    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
    //    {
    //        auto levelSample = oscillator->getNextSample() * Output_level;                         // [9]

    //        leftBuffer[sample] += levelSample;                                             // [10]
    //        rightBuffer[sample] += levelSample;
    //    }
    //}

    /*Output*/
    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        auto levelSample = oscillators[0]->getNextSample();
        auto LFO_levelSample = LFO_oscillators[0]->getNextSample() * LFO_level;
        //leftBuffer[sample] += levelSample;
        //rightBuffer[sample] += levelSample;

        //leftBuffer[sample] += LFO_levelSample;
        //rightBuffer[sample] += LFO_levelSample;

        /*VCO_syncState*/
        if (VCO_syncState) {
            if (LFO_level != 0.0f) {
                leftBuffer[sample] += (levelSample + LFO_levelSample) * Output_level;
                rightBuffer[sample] += (levelSample + LFO_levelSample) * Output_level;
            }
            else
            {
                leftBuffer[sample] += levelSample * Output_level;
                rightBuffer[sample] += levelSample * Output_level;
            }
        } // END if VCO_syncState
        /*!VCO_syncState*/
        else {
            if (LFO_level != 0.0f) {
                leftBuffer[sample] += levelSample * LFO_levelSample * Output_level;
                rightBuffer[sample] += levelSample * LFO_levelSample * Output_level;
            }
            else
            {
                leftBuffer[sample] += levelSample * Output_level;
                rightBuffer[sample] += levelSample * Output_level;
            }
        } // END if !VCO_syncState
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    /**
    * https://docs.juce.com/master/classImageCache.html#details
    * https://forum.juce.com/t/how-to-add-a-background-image/21454
    */
    auto imageBackground = juce::ImageCache::getFromMemory(BinaryData::Background_PNG, BinaryData::Background_PNGSize);
    g.drawImageAt(imageBackground, 0, 0);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    /*Output*/
    const int Output_dialRadius{ 40 };
    const int Output_dialDiameter{ Output_dialRadius * 2 };
    const int Output_dialY{ 272 };
    const int Output_dialX_volume{ 656 };
    Output_volume_dial.setBounds(Output_dialX_volume - Output_dialRadius, Output_dialY - Output_dialRadius, Output_dialDiameter, Output_dialDiameter);
    Output_volume_dial.addListener(this);

    /*VCO dials*/
    const int VCO_dialRadius{ 40 };
    const int VCO_dialDiameter{ VCO_dialRadius * 2 };
    const int VCO_toggleButtonRadius{ 20 };
    const int VCO_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int VCO_dialY{ 165 };
    const int VCO_dialX_frequency{ 128 };
    const int VCO_dialX_LFO_ModDepth{ 320 };
    const int VCO_dialX_AR_ModDepth{ 448 };
    const int VCO_syncToggleButtonX{ 224 };
    const int VCO_ARmodToggleButtonX{ 548 };
    VCO_frequency_dial.setBounds(VCO_dialX_frequency - VCO_dialRadius, VCO_dialY - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);
    VCO_LFO_ModDepth_dial.setBounds(VCO_dialX_LFO_ModDepth - VCO_dialRadius, VCO_dialY - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);
    VCO_AR_ModDepth_dial.setBounds(VCO_dialX_AR_ModDepth - VCO_dialRadius, VCO_dialY - VCO_dialRadius, VCO_dialDiameter, VCO_dialDiameter);
    VCO_sync_toggleButton.setBounds(VCO_syncToggleButtonX - VCO_toggleButtonRadius, VCO_dialY - VCO_toggleButtonRadius, VCO_toggleButtonDiameter, VCO_toggleButtonDiameter);
    VCO_ARmod_toggleButton.setBounds(VCO_ARmodToggleButtonX - VCO_toggleButtonRadius, VCO_dialY - VCO_toggleButtonRadius, VCO_toggleButtonDiameter, VCO_toggleButtonDiameter);


    /*VCLPF dials*/
    const int VCLPF_dialRadius{ 40 };
    const int VCLPF_dialDiameter{ VCLPF_dialRadius * 2 };
    const int VCLPF_toggleButtonRadius{ 20 };
    const int VCLPF_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int VCLPF_dialY{ 352 };
    const int VCLPF_dialX_cutoffFrequency{ 260 };
    const int VCLPF_dialX_resonance{ 388 };
    const int VCLPF_dialX_ModDepth{ 514 };
    const int VCLPF_whiteNoiseToggleButtonX{ 106 };
    const int VCLPF_whiteNoiseToggleButtonY{ 398 };
    const int VCLPF_LFOToggleButtonX{ 515 };
    const int VCLPF_LFOToggleButtonY{ 470 };
    VCLPF_cutoffFrequency_dial.setBounds(VCLPF_dialX_cutoffFrequency - VCLPF_dialRadius, VCLPF_dialY - VCLPF_dialRadius, VCLPF_dialDiameter, VCLPF_dialDiameter);
    VCLPF_resonance_dial.setBounds(VCLPF_dialX_resonance - VCLPF_dialRadius, VCLPF_dialY - VCLPF_dialRadius, VCLPF_dialDiameter, VCLPF_dialDiameter);
    VCLPF_ModDepth_dial.setBounds(VCLPF_dialX_ModDepth - VCLPF_dialRadius, VCLPF_dialY - VCLPF_dialRadius, VCLPF_dialDiameter, VCLPF_dialDiameter);
    VCLPF_inputSelect_dial.setBounds(108 - VCLPF_dialRadius, 314 - VCLPF_dialRadius, VCLPF_dialDiameter, VCLPF_dialDiameter);
    VCLPF_whiteNoise_toggleButton.setBounds(VCLPF_whiteNoiseToggleButtonX - VCLPF_toggleButtonRadius, VCLPF_whiteNoiseToggleButtonY - VCLPF_toggleButtonRadius, VCLPF_toggleButtonDiameter, VCLPF_toggleButtonDiameter);
    VCLPF_LFO_toggleButton.setBounds(VCLPF_LFOToggleButtonX - VCLPF_toggleButtonRadius, VCLPF_LFOToggleButtonY - VCLPF_toggleButtonRadius, VCLPF_toggleButtonDiameter, VCLPF_toggleButtonDiameter);

    /*AREG dials*/
    const int AREG_dialRadius{ 40 };
    const int AREG_dialDiameter{ AREG_dialRadius * 2 };
    const int AREG_toggleButtonRadius{ 20 };
    const int AREG_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int AREG_dialY{ 552 };
    const int AREG_dialX_attack{ 128 };
    const int AREG_dialX_release{ 268 };
    AREG_attack_dial.setBounds(AREG_dialX_attack - AREG_dialRadius, AREG_dialY - AREG_dialRadius, AREG_dialDiameter, AREG_dialDiameter);
    AREG_release_dial.setBounds(AREG_dialX_release - AREG_dialRadius, AREG_dialY - AREG_dialRadius, AREG_dialDiameter, AREG_dialDiameter);
    AREG_repeat_toggleButton.setBounds(206 - AREG_toggleButtonRadius, 680 - AREG_toggleButtonRadius, AREG_toggleButtonDiameter, AREG_toggleButtonDiameter);
    AREG_manualGate_toggleButton.setBounds(112 - AREG_toggleButtonRadius, 680 - AREG_toggleButtonRadius, AREG_toggleButtonDiameter, AREG_toggleButtonDiameter);

    /*LFO dials*/
    const int LFO_dialRadius{ 40 };
    const int LFO_dialDiameter{ LFO_dialRadius * 2 };
    const int LFO_toggleButtonRadius{ 20 };
    const int LFO_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int LFO_dialY{ 658 };
    const int LFO_dialX{ 516 };
    LFO_rate_dial.setBounds(LFO_dialX - LFO_dialRadius, LFO_dialY - LFO_dialRadius, LFO_dialDiameter, LFO_dialDiameter);
    LFO_integrate_toggleButton.setBounds(408 - LFO_toggleButtonRadius, 534 - LFO_toggleButtonRadius, LFO_toggleButtonDiameter, LFO_toggleButtonDiameter);
    LFO_derivate_toggleButton.setBounds(408 - LFO_toggleButtonRadius, 660 - LFO_toggleButtonRadius, LFO_toggleButtonDiameter, LFO_toggleButtonDiameter);

    /*VCA dials*/
    const int VCA_toggleButtonRadius{ 20 };
    const int VCA_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int VCA_ToggleButtonX{ 659 };
    const int VCA_ToggleButtonY{ 469 };
    VCA_toggleButton.setBounds(VCA_ToggleButtonX - VCA_toggleButtonRadius, VCA_ToggleButtonY - VCA_toggleButtonRadius, VCA_toggleButtonDiameter, VCA_toggleButtonDiameter);

    /*PWR dials*/
    const int PWR_toggleButtonRadius{ 20 };
    const int PWR_toggleButtonDiameter{ VCO_toggleButtonRadius * 2 };
    const int PWR_ToggleButtonX{ 654 };
    const int PWR_ToggleButtonY{ 654 };
    PWR_toggleButton.setBounds(PWR_ToggleButtonX - PWR_toggleButtonRadius, PWR_ToggleButtonY - PWR_toggleButtonRadius, PWR_toggleButtonDiameter, PWR_toggleButtonDiameter);

}

void MainComponent::buttonClicked(juce::Button* button)
{
    /*VCO_sync_toggleButton*/
    if (button == &VCO_sync_toggleButton)
    {
        if (!VCO_syncState) {
            VCO_syncState = true;
            VCO_sync_toggleButton.setButtonText("ON");
        }
        else {
            VCO_syncState = false;
            VCO_sync_toggleButton.setButtonText("OFF");
        }
    }

    /*VCO_ARmod_toggleButton*/
    if (button == &VCO_ARmod_toggleButton)
    {
        if (!VCO_ARmodState) {
            VCO_ARmodState = true;
            VCO_ARmod_toggleButton.setButtonText("ON");
        }
        else {
            VCO_ARmodState = false;
            VCO_ARmod_toggleButton.setButtonText("OFF");
        }
    }

    /*VCLPF_whiteNoise_toggleButton*/
    if (button == &VCLPF_whiteNoise_toggleButton)
    {
        if (!VCLPF_whiteNoiseState) {
            VCLPF_whiteNoiseState = true;
            VCLPF_whiteNoise_toggleButton.setButtonText("ON");
        }
        else {
            VCLPF_whiteNoiseState = false;
            VCLPF_whiteNoise_toggleButton.setButtonText("OFF");
        }
    }

    /*VCLPF_LFO_toggleButton*/
    if (button == &VCLPF_LFO_toggleButton)
    {
        if (!VCLPF_LFOState) {
            VCLPF_LFOState = true;
            VCLPF_LFO_toggleButton.setButtonText("LFO");
        }
        else {
            VCLPF_LFOState = false;
            VCLPF_LFO_toggleButton.setButtonText("AR");
        }
    }


    /*VCA_toggleButton*/
    if (button == &VCA_toggleButton)
    {
        if (!VCA_state) {
            VCA_state = true;
            VCA_toggleButton.setButtonText("ON");
        }
        else {
            VCA_state = false;
            VCA_toggleButton.setButtonText("OFF");
        }
    }

    /*PWR_toggleButton*/
    if (button == &PWR_toggleButton)
    {
        if (!PWR_state) {
            PWR_state = true;
            PWR_toggleButton.setButtonText("ON");
        }
        else {
            PWR_state = false;
            PWR_toggleButton.setButtonText("OFF");
        }
    }

    /*LFO_integrate_toggleButton*/
    if (button == &LFO_integrate_toggleButton)
    {
        if (!LFO_integrate_state) {
            LFO_integrate_state = true;
            LFO_integrate_toggleButton.setButtonText("I");
            LFO_createWavetable();
        }
        else {
            LFO_integrate_state = false;
            LFO_integrate_toggleButton.setButtonText("OFF");
            LFO_createWavetable();
        }
    }

    /*LFO_derivate_toggleButton*/
    if (button == &LFO_derivate_toggleButton)
    {
        if (!LFO_derivate_state) {
            LFO_derivate_state = true;
            LFO_derivate_toggleButton.setButtonText("D");
            LFO_createWavetable();
        }
        else {
            LFO_derivate_state = false;
            LFO_derivate_toggleButton.setButtonText("OFF");
            LFO_createWavetable();
        }
    }

    /*AREG_repeat_toggleButton*/
    if (button == &AREG_repeat_toggleButton)
    {
        if (!AREG_repeat_state) {
            AREG_repeat_state = true;
            AREG_repeat_toggleButton.setButtonText("R");
        }
        else {
            AREG_repeat_state = false;
            AREG_repeat_toggleButton.setButtonText("M");
        }
    }

    /*AREG_manualGate_toggleButton*/
    if (button == &AREG_manualGate_toggleButton)
    {

    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    /*VCO_frequency_dial*/
    if (slider == &VCO_frequency_dial) 
    {
        /*Change VCO frequency*/
        VCO_frequency = VCO_frequency_dial.getValue();
        VCO_setFrequencies();
    }

    /*Output_volume_dial*/
    if (slider == &Output_volume_dial)
    {
        Output_volume.setGainLinear(Output_volume_dial.getValue());
        Output_level = Output_volume_dial.getValue();
    }

    /*LFO_rate_dial*/
    if (slider == &LFO_rate_dial)
    {
        LFO_frequency = LFO_rate_dial.getValue();
        LFO_setFrequencies();
    }

    /*VCO_LFO_ModDepth_dial*/
    if (slider == &VCO_LFO_ModDepth_dial)
    {
        LFO_level = VCO_LFO_ModDepth_dial.getValue();
    }
}
void MainComponent::VCO_createWavetable()
{
    sawtoothTable.setSize(1, (int)VCO_tableSize);
    auto* samples = sawtoothTable.getWritePointer(0);

    auto angleDelta = juce::MathConstants<double>::twoPi / (double)(VCO_tableSize - 1);
    auto currentAngle = 0.0;

    for (unsigned int i = 0; i < VCO_tableSize; ++i)
    {
        //auto sample = std::sin(currentAngle);
        auto sample = (float)(i / (float)VCO_tableSize);
        samples[i] = (float)sample;
        currentAngle += angleDelta;
    }

}
void MainComponent::LFO_createWavetable()
{
    LFO_waveTable.setSize(1, (int)LFO_tableSize);
    auto* samples = LFO_waveTable.getWritePointer(0);
    const auto RC = 1000 * 0.0000033f;

    auto angleDelta = juce::MathConstants<double>::twoPi / (double)(LFO_tableSize - 1);
    auto currentAngle = 0.0;

    /*Square*/
    if ( (!LFO_integrate_state && !LFO_derivate_state) || (LFO_integrate_state && LFO_derivate_state)) {
        

        for (unsigned int i = 0; i < LFO_tableSize; ++i)
        {
            //auto sample = std::sin(currentAngle);
            //samples[i] = (float)sample;
            if (currentAngle <= juce::MathConstants<float>::pi) samples[i] = 1.0f;
            else samples[i] = -1.0f;
            currentAngle += angleDelta;
        }
    }
    /*RC charge-discharge*/
    if (LFO_integrate_state && !LFO_derivate_state) 
    {
        /*Charge*/
        for (unsigned int i = 0; i < (1 * (LFO_tableSize / 4) - 1); ++i)
        {
            auto sample = 1 - std::exp(((-currentAngle) / RC));
            samples[i] = (float)sample;
            currentAngle += angleDelta;
        }
        /*Discharge*/
        for (unsigned int i = (1 * (LFO_tableSize/4)); i < (2*(LFO_tableSize/4)-1); ++i)
        {
            auto sample = std::exp(((-currentAngle) / RC));
            samples[i] = (float)sample;
            currentAngle += angleDelta;
        }
        /*Charge*/
        for (unsigned int i = (2 * (LFO_tableSize / 4)); i < (3 * (LFO_tableSize / 4) - 1); ++i)
        {
            auto sample = -1 + std::exp(((-currentAngle) / RC));
            samples[i] = (float)sample;
            currentAngle += angleDelta;
        }
        /*Discharge*/
        for (unsigned int i = (3 * (LFO_tableSize / 4)) / 2; i < (4 * (LFO_tableSize / 4) - 1) / 2; ++i)
        {
            auto sample = -std::exp(((-currentAngle) / RC));
            samples[i] = (float)sample;
            currentAngle += angleDelta;
        }
    }
    /*Spikes*/
    if (LFO_derivate_state && !LFO_integrate_state)
    {
        for (unsigned int i = 0; i < LFO_tableSize / 2 - 1; ++i)
        {
            auto sample = std::exp(((-currentAngle) / RC));
            samples[i] = (float)sample;
            currentAngle += angleDelta;
        }
        for (unsigned int i = LFO_tableSize / 2; i < LFO_tableSize / 2; ++i)
        {
            auto sample = -std::exp(((-currentAngle) / RC));
            samples[i] = (float)sample;
            currentAngle += angleDelta;
        }
    }
}
void MainComponent::VCO_setFrequencies()
{
    oscillators[0]->setFrequency(VCO_frequency, samplerate);
}
void MainComponent::LFO_setFrequencies()
{
    LFO_oscillators[0]->setFrequency(LFO_frequency, samplerate);
}