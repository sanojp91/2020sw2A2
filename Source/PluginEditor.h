/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
//creating a new class for look and feel based on the JUCE tutorial
class OtherLookAndFeel : public LookAndFeel_V4
{
    
public:
    OtherLookAndFeel()
    {
        setColour (Slider::thumbColourId, Colours::darkkhaki);
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        //fill
        g.setColour (Colours::antiquewhite);
        g.fillEllipse (rx, ry, rw, rw);
        
        //outline
        g.setColour (Colours::black);
        g.drawEllipse(rx, ry, rw, rw, 4.0f);
        
        Path p;
        auto pointerLength = radius * 0.66f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, - radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        //pointer
        g.setColour (Colours::black);
        g.fillPath (p);
        
    }
    

    
};

class _2020sw2a2AudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener,
                                        public Button::Listener

{
public:
    _2020sw2a2AudioProcessorEditor (_2020sw2a2AudioProcessor&);
    ~_2020sw2a2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button* button) override;
    
    Slider mFreqSlider;
    Slider mMixSlider;
    Slider mGainSlider;
    ToggleButton mBypassButton;
    
private:
    //declaring the background image
    Image PlugBG;
    
    OtherLookAndFeel otherLookAndFeel;
   
    //declaring frequency slider 
   // Slider mFreqSlider;
    Label mFreqLabel;
    
    //declaring a mix slider
    //Slider mMixSlider;
    Label mMixLabel;
    
    //declaring a slider and label for the gain
   // Slider mGainSlider;
    Label mGainLabel;
    
   // TextButton mBypassButton;
    Label mBypassLabel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _2020sw2a2AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2a2AudioProcessorEditor)
};
