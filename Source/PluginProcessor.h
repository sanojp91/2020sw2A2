/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class _2020sw2a2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    _2020sw2a2AudioProcessor();
    ~_2020sw2a2AudioProcessor();

    //==============================================================================
    
    //update the sine wave frequency according to the sample rate
    void updateAngleDelta()
    {
        auto cyclesPerSample = mFreq / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
    }
    

    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
    //void processBlockBypassed (AudioBuffer<float>&inBuffer, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float mFreq { 800 };
    float mMix { 0.0f };
    bool mByPass {false};
    void setByPass(bool t);
    SmoothedValue<float> mGain;
  
    
private:

    //declaring variables for the sine wave
    double currentSampleRate = 0.0;
    double currentAngle = 0.0;
    double angleDelta = 0.0;
 
   // SmoothedValue<float> mGain;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2a2AudioProcessor)
};
