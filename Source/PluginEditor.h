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
    
  /*  void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, const float minSliderPos, const int maxSliderPos, const Slider::SliderStyle, Slider& slider) //override
    {
        auto middle = jmin (width / 2, height / 2);
        auto centreX = x + width * 0.5;
        auto centreY = y + height * 0.5;
        
        g.setColour (Colours::antiquewhite);
       // g.fillRect (middle, centreX, centreY);
        
        g.setColour(Colours::black);
       // g.drawRect(<#float x#>, <#float y#>, <#float width#>, <#float height#>)
        
        
    }
    */
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
    
   void drawButtonBackground (Graphics g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) //override
    {
        
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;
        
        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);
        
        //shadow
        g.setColour (Colours::darkgrey.withAlpha (0.5f));
        g.fillRect (buttonArea);
        
        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);
        
        g.setColour (backgroundColour);
        g.fillRect (buttonArea);
        
    }
    
    void drawButtonText (Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
    {
        
        auto font = getTextButtonFont (button, button.getHeight());
        g.setFont (font);
        g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId : TextButton::textColourOffId).withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));
        
        auto yIndent = jmin (4, button.proportionOfHeight (0.3f));
        auto cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;
        auto fontHeight = roundToInt (font.getHeight() * 0.6f);
        auto leftIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
        auto rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
        
        auto textWidth = button.getWidth() - leftIndent - rightIndent;
        
        auto edge = 4;
        auto offset = isButtonDown ? edge / 2 : 0;
        
        if (textWidth > 0)
            g.drawFittedText (button.getButtonText(), leftIndent + offset, yIndent + offset, textWidth, button.getHeight() - yIndent * 2 - edge, Justification::centred, 2);
        
    }
    
};

class _2020sw2a2AudioProcessorEditor  : public AudioProcessorEditor,
                                        public Slider::Listener

{
public:
    _2020sw2a2AudioProcessorEditor (_2020sw2a2AudioProcessor&);
    ~_2020sw2a2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged (Slider* slider) override;
    
private:
    //declaring the background image
    Image PlugBG;
    
   // LookAndFeel_V4 otherLookAndFeel;
    
    //LookAndFeel_V4 otherLookAndFeel2;
    
    OtherLookAndFeel otherLookAndFeel;
   
    //declaring frequency slider 
    Slider mFreqSlider;
    Label mFreqLabel;
    
    //declaring a mix slider
    Slider mMixSlider;
    Label mMixLabel;
    
    //declaring a slider for input gain
    Slider mInputGain;
    Label mInputLabel;
    
    //declaring a slider and label for the gain
    Slider mGainSlider;
    Label mGainLabel;
    
    TextButton mBypassButton;
    Label mBypassLabel;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _2020sw2a2AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_2020sw2a2AudioProcessorEditor)
};
