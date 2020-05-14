/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_2020sw2a2AudioProcessorEditor::_2020sw2a2AudioProcessorEditor (_2020sw2a2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    
    auto& params = processor.getParameters();
    
    //initilizing the background image
    PlugBG = ImageCache::getFromMemory(BinaryData::PlugBG_jpg, BinaryData::PlugBG_jpgSize);

    //set up look and feel for sliders
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::black);
    
    //otherLookAndFeel.setColour(Slider::thumbColourId, Colours::azure);
    mInputGain.setLookAndFeel(&otherLookAndFeel);
    mMixSlider.setLookAndFeel(&otherLookAndFeel);
    mBypassButton.setLookAndFeel(&otherLookAndFeel);
    mGainSlider.setLookAndFeel(&otherLookAndFeel);
    
   /* otherLookAndFeel2.setColour(Slider::thumbColourId, Colours::darkkhaki);
    mInputGain.setLookAndFeel(&otherLookAndFeel2);
    mGainSlider.setLookAndFeel(&otherLookAndFeel2);
    */
    
    
    
    
    //Frequency slider
    //AudioParameterFloat* freqParameter = (AudioParameterFloat*)params.getUnchecked(1);
    mFreqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
   // mFreqSlider.setRange(freqParameter->range.start, freqParameter->range.end, 0.01f);
   // mFreqSlider.setValue(*freqParameter);
    mFreqSlider.setRange(60.f, 16000.f, 0.01);
    mFreqSlider.setValue(800.f);
    mFreqSlider.setTextValueSuffix(" Hz");
    mFreqSlider.addListener(this);
    mFreqSlider.setSkewFactorFromMidPoint(1000.0f);
    addAndMakeVisible(mFreqSlider);
    

    
   // mFreqSlider.onValueChange = [this, freqParameter] {*freqParameter = mFreqSlider.getValue(); };
   // mFreqSlider.onDragStart = [freqParameter] {freqParameter->beginChangeGesture(); };
  //  mFreqSlider.onDragEnd = [freqParameter] {freqParameter->endChangeGesture(); };
    
    mFreqLabel.setText("Freq", dontSendNotification);
    mFreqLabel.attachToComponent(&mFreqSlider, true);
    addAndMakeVisible(mFreqLabel);
    
    // Mix slider
    AudioParameterFloat* mixParameter = (AudioParameterFloat*)params.getUnchecked(0);
    mMixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mMixSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 30);
    mMixSlider.setRange(mixParameter->range.start, mixParameter->range.end, 0.01f);
    mMixSlider.setValue(*mixParameter);
    mMixSlider.setTextValueSuffix(" %");
    //mMixSlider.addListener(this);
   // mMixSlider.setSkewFactor(mixParameter->range.symmetricSkew, true);
    addAndMakeVisible(mMixSlider);
    
    mMixSlider.onValueChange = [this, mixParameter] { *mixParameter = mMixSlider.getValue(); };
    mMixSlider.onDragStart = [mixParameter] {mixParameter->beginChangeGesture(); };
    mMixSlider.onDragEnd = [mixParameter] {mixParameter->endChangeGesture(); };
    
    mMixLabel.setText("Mix", dontSendNotification);
    mMixLabel.attachToComponent(&mMixSlider, false);
    addAndMakeVisible(mMixLabel);
    
    //Input gain slider
    mInputGain.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mInputGain.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 30);
    mInputGain.setRange(-40.0f, 20.0f, 0.1f);
    mInputGain.setValue(0.0f);
    mInputGain.setTextValueSuffix("dB");
    mInputGain.addListener(this);
    mInputGain.setSkewFactorFromMidPoint(0.0f);
    addAndMakeVisible(mInputGain);
    
    mInputLabel.setText("Input", dontSendNotification);
    mInputLabel.attachToComponent(&mInputGain, false);
    addAndMakeVisible(mInputLabel);
    
    //Output gain slider
    mGainSlider.setSliderStyle (Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 50, 20);
    mGainSlider.setRange (-60.0f, 20.0f, 0.1f);
    mGainSlider.setTextValueSuffix(" dB");
    mGainSlider.setValue(0.0f);
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);
    
    mGainLabel.setText("Output", dontSendNotification);
    mGainLabel.attachToComponent(&mGainSlider, false);
    addAndMakeVisible(mGainLabel);
    
    mBypassButton.setToggleState(false, dontSendNotification);
    mBypassButton.setButtonText("Bypass");
    //mBypassButton.addListener(this);
    addAndMakeVisible(mBypassButton);
    
   // mBypassLabel.setText("Bypass", dontSendNotification);
   // mBypassLabel.attachToComponent(mBypassButton, false);
    
    //mBypassButton.tickColourId (ToggleButton::ColourIds::)
    //mBypassButton.textColourId (ToggleButton::ColourIds::white);
    
    // editor's size
    setSize (400, 300);

}

_2020sw2a2AudioProcessorEditor::~_2020sw2a2AudioProcessorEditor()
{
}

//==============================================================================
void _2020sw2a2AudioProcessorEditor::paint (Graphics& g)
{
    //drawing the background image
    g.drawImageWithin(PlugBG, 0, 0, getWidth(), getHeight(), RectanglePlacement::fillDestination);
    
    // fill the background with black
    //g.fillAll(Colours::black);
    
    g.setColour (Colours::indianred);
    g.setFont (15.0f);
    //g.drawFittedText ("Ring modulation at a fixed 800Hz frequency", getLocalBounds(), Justification::centred, 1);
    
}


void _2020sw2a2AudioProcessorEditor::resized()
{
    // Positions for the sliders & buttons
    mFreqSlider.setBounds(getWidth() / 4 - 50, getHeight() - 300, 300, 70);
    
    mMixSlider.setBounds(getWidth() / 4 + 50, getHeight() / 2, 100, 150);
    
    mInputGain.setBounds(getWidth() - 375, getHeight() / 2, 100, 150);
    
    mGainSlider.setBounds(getWidth() - 100, getHeight() / 2, 100, 150);
    
    mBypassButton.setBounds(getWidth() - 50, getHeight() - 300, 50, 20);
    
}

void _2020sw2a2AudioProcessorEditor::sliderValueChanged (Slider *slider)
{
    
     if (slider == &mFreqSlider)
     {
         
         processor.mFreq = mFreqSlider.getValue();
        
         
     }
    else if (slider == &mGainSlider)
    {
        
        processor.mGain = mGainSlider.getValue();
        
    }
   /* else if (slider == &mMixSlider)
    {
        
        processor.mMix = mMixSlider.getValue();
        
    }
    */
}



