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
    
    //initilizing the background image
    PlugBG = ImageCache::getFromMemory(BinaryData::PlugBG_jpg, BinaryData::PlugBG_jpgSize);

    //set up look and feel for sliders
    getLookAndFeel().setColour(Slider::thumbColourId, Colours::black);
    
    mMixSlider.setLookAndFeel(&otherLookAndFeel);
    //mGainSlider.setLookAndFeel(&otherLookAndFeel);
    //mFreqSlider.setLookAndFeel(&otherLookAndFeel);

    
    //Frequency slider
    mFreqSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    mFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 30);
    mFreqSlider.setRange(60.f, 16000.f, 0.01);
    mFreqSlider.setValue(800.f);
    mFreqSlider.setTextValueSuffix(" Hz");
    mFreqSlider.addListener(this);
    mFreqSlider.setSkewFactorFromMidPoint(1000.0f);
    addAndMakeVisible(mFreqSlider);
    
    mFreqLabel.setText("Freq", dontSendNotification);
    mFreqLabel.attachToComponent(&mFreqSlider, true);
    addAndMakeVisible(mFreqLabel);
    
    // Mix slider
    //AudioParameterFloat* mixParameter = (AudioParameterFloat*)params.getUnchecked(0);
    mMixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mMixSlider.setTextBoxStyle(Slider::TextBoxAbove, true, 80, 30);
    mMixSlider.setRange(0.f, 100.f, 0.01f);
    mMixSlider.setValue(50.f);
    mMixSlider.setTextValueSuffix(" %");
    mMixSlider.addListener(this);
    addAndMakeVisible(mMixSlider);
    
    mMixLabel.setText("Mix", dontSendNotification);
    mMixLabel.attachToComponent(&mMixSlider, false);
    addAndMakeVisible(mMixLabel);

    
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
    
    
    mBypassButton.setClickingTogglesState(true);
    mBypassButton.setButtonText("OFF");
    mBypassButton.setState(Button::ButtonState::buttonNormal);
    mBypassButton.addListener(this);
    addAndMakeVisible(mBypassButton);
    
    // editor's size
    setSize (400, 300);

}

_2020sw2a2AudioProcessorEditor::~_2020sw2a2AudioProcessorEditor()
{
    mMixSlider.setLookAndFeel(nullptr);
    mGainSlider.setLookAndFeel(nullptr);
    mFreqSlider.setLookAndFeel(nullptr);

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
        
        processor.mGain.setTargetValue(mGainSlider.getValue());
        
    }
    else if (slider == &mMixSlider)
    {
        
        processor.mMix = mMixSlider.getValue();
        
    }
    
}

void _2020sw2a2AudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &mBypassButton)
    {
        if (button->getToggleState())
        {
            mBypassButton.setButtonText("ON");
            processor.setByPass(true);
            
        }
        else
        {
            mBypassButton.setButtonText("OFF");
            processor.setByPass(false);
            
        }
        
        
    }

    
}

