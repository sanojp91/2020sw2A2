/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_2020sw2a2AudioProcessor::_2020sw2a2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ) , parameters(*this, nullptr, Identifier("RingMod"),
                        {
                            std::make_unique<AudioParameterFloat>("freq", // ID name
                                                                  "Frequency", // Host name that shows up in DAW
                                                                  60.0f, //min value
                                                                  2000.0f, //max value
                                                                  800.0f), //default value
                           
                           std::make_unique<AudioParameterFloat>("gain",
                                                                 "Gain",
                                                                 0.0f,
                                                                 2.0f,
                                                                 1.0f),
                           std::make_unique<AudioParameterFloat>("mix",
                                                                 "Mix",
                                                                 0.0f,
                                                                 100.0f,
                                                                 100.0f),
                           std::make_unique<AudioParameterBool>("bypass",
                                                                "Bypass",
                                                                false)
                        })
#endif
{
   // initialazation
    freqParameter = parameters.getRawParameterValue("freq");
    gainParameter = parameters.getRawParameterValue("gain");
    mixParameter = parameters.getRawParameterValue("mix");
    byPassParameter = parameters.getRawParameterValue("bypass");
}

_2020sw2a2AudioProcessor::~_2020sw2a2AudioProcessor()
{
}

//==============================================================================
const String _2020sw2a2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool _2020sw2a2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _2020sw2a2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _2020sw2a2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double _2020sw2a2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _2020sw2a2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _2020sw2a2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void _2020sw2a2AudioProcessor::setCurrentProgram (int index)
{
}

const String _2020sw2a2AudioProcessor::getProgramName (int index)
{
    return {};
}

void _2020sw2a2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void _2020sw2a2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //setting the sample rate and updating to the sinewave generator
    {
    currentSampleRate = sampleRate;
    
        
    
    //mGain.reset(sampleRate, 0.05f);
   // mGain.setTargetValue(0.f);
        
    updateAngleDelta();
    
    //mFreq = *freqParameter;
        
   // mByPass = *byPassParameter;
    //mByPass = false;
    *byPassParameter = false;
        
    }
    

}

void _2020sw2a2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool _2020sw2a2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void _2020sw2a2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //when mFreq value changes update the angle delta function
    if (currentSampleRate > 0.0)
    {
        updateAngleDelta();
    }
    
    //iterating through the output channels
    for (auto channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        //get read pointer for the input and write pointer for the output
        auto* inBuffer = buffer.getReadPointer(channel);
        auto* outBuffer = buffer.getWritePointer(channel);
        

        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            
           
            if (*byPassParameter)
            {
            //creating the sinewave and having it modulate incoming audio
                outBuffer[sample] = inBuffer[sample] * (float) std::sin(currentAngle) * 0.5  * *gainParameter; //Decibels::decibelsToGain(mGain.getNextValue()); 
            }
            
            else
            {
                
                outBuffer[sample] = inBuffer[sample] * *gainParameter; //Decibels::decibelsToGain(mGain.getNextValue());
                
            }
            
             currentAngle += angleDelta;
           // dry = ((1 - mMix) * dryBuffer) + (mMix * inBuffer):
          //  outBuffer[sample] = ((1 - mMix) * cleanOut) + (mMix * input);
                      
        }
        
    }
    
    // In case we have more outputs than inputs, this code clears any output
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

}

//==============================================================================
bool _2020sw2a2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* _2020sw2a2AudioProcessor::createEditor()
{
    return new _2020sw2a2AudioProcessorEditor (*this, parameters); //create a listener to the apvts
}

//==============================================================================
void _2020sw2a2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml()); //store the parameters state
    copyXmlToBinary(*xml, destData); //saves the pointer xml to have it saved when the plugin is closed
    
}

void _2020sw2a2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes)); //get the xml data from the memory
    if (xmlState.get() != nullptr)
    {
        
        if (xmlState -> hasTagName(parameters.state.getType()))
        {
            
            parameters.replaceState(ValueTree::fromXml(*xmlState)); //replace all of the data in the parameters with the saved data
            
        }
        
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _2020sw2a2AudioProcessor();
}


/*void _2020sw2a2AudioProcessor::setByPass(bool b)
{
    
    mByPass = b;
    
}
*/
