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
        auto cyclesPerSample = currentFrequency / currentSampleRate;
        angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
    }
    
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

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

private:
    
    //declaring variables for the sine wave
    double currentSampleRate = 0.0;
    double currentAngle = 0.0;
    double angleDelta = 0.0;
    // I set the frequency to 800 because I felt that it gives a pretty good sound in regards to not being overly "piercy" with high frequencies or too "bassy"
    double currentFrequency = 800;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2a2AudioProcessor)
};
