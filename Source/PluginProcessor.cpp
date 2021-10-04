/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyNoiseToasterAudioProcessor::MyNoiseToasterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), false)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , apvts(*this, nullptr, "Parameters", createParams()),
    noiseToasterData(apvts)
{
    
}

MyNoiseToasterAudioProcessor::~MyNoiseToasterAudioProcessor()
{
}

//==============================================================================
const juce::String MyNoiseToasterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyNoiseToasterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyNoiseToasterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyNoiseToasterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyNoiseToasterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyNoiseToasterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyNoiseToasterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyNoiseToasterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MyNoiseToasterAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyNoiseToasterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MyNoiseToasterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    noiseToasterData.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void MyNoiseToasterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyNoiseToasterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MyNoiseToasterAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    /*From JUCE*/
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    if(PWR_state)
    {
        /*noiseToasterData*/
        noiseToasterData.processBlock(buffer, midiMessages);

        /*Scope*/
        oscilloscope.pushBuffer(buffer);
    }
    else
    {
        oscilloscope.clear();
    }
}

//==============================================================================
bool MyNoiseToasterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MyNoiseToasterAudioProcessor::createEditor()
{
    return new MyNoiseToasterAudioProcessorEditor (*this);
}

//==============================================================================
void MyNoiseToasterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MyNoiseToasterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void MyNoiseToasterAudioProcessor::VCO_changeWave()
{
    switch(VCO_waveType)
    {
        case WaveType::Sawtooh:
        {
            /**/
            auto& osc = processorChain.template get<VCO_oscIndex>();
            osc.initialise([](float x) { return (x / juce::MathConstants<float>::pi); }, BUFFER_SIZE);
            osc.setFrequency(VCO_frequency); 
            break;
        }
        case WaveType::Square:
        {
            /**/
            auto& osc = processorChain.template get<VCO_oscIndex>();
            osc.initialise([](float x) { return ((x < 0.0f) ? (-1.0f) : (1.0f)); }, BUFFER_SIZE);
            osc.setFrequency(VCO_frequency);
            break;
        }
        case WaveType::Off:
        default:
        {
            /**/
            auto& osc = processorChain.template get<VCO_oscIndex>();
            osc.initialise([](float x) { return 0.0f; }, BUFFER_SIZE);
            osc.setFrequency(VCO_frequency);
            break;
        }
    }
}
void MyNoiseToasterAudioProcessor::LFO_changeWave()
{

}
void MyNoiseToasterAudioProcessor::Output_setGain() 
{
    /**/
    auto& gain = processorChain.template get<Output_gainIndex>();
    gain.setGainLinear(Output_gain);
}
void MyNoiseToasterAudioProcessor::VCO_setFrequency() 
{
    /**/
    auto& osc = processorChain.template get<VCO_oscIndex>();
    osc.setFrequency(VCO_frequency);
}
void MyNoiseToasterAudioProcessor::LFO_setFrequency()
{
    lfo.setFrequency(LFO_frequency);
}
void MyNoiseToasterAudioProcessor::VCLPF_setFrequency()
{
    auto& filter = processorChain.get<VCLPF_filterIndex>();
    filter.setCutoffFrequencyHz(VCLPF_cutoffFrequency);
}
void MyNoiseToasterAudioProcessor::VCLPF_setResonance()
{
    auto& filter = processorChain.get<VCLPF_filterIndex>();
    filter.setResonance(VCLPF_resonance);
}
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyNoiseToasterAudioProcessor();
}

/*Value tree*/
juce::AudioProcessorValueTreeState::ParameterLayout MyNoiseToasterAudioProcessor::createParams()
{
    /*Parameter vector*/
    std::vector< std::unique_ptr< juce::RangedAudioParameter > > params;

    /*OSC select*/
    params.push_back(std::make_unique<juce::AudioParameterChoice>("osc1wavetype", "Osc1 wave type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    /*ADSR*/
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    /*Return*/
    return { params.begin(), params.end() };
}
