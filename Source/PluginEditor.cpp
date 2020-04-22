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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

_2020sw2a2AudioProcessorEditor::~_2020sw2a2AudioProcessorEditor()
{
}

//==============================================================================
void _2020sw2a2AudioProcessorEditor::paint (Graphics& g)
{
      // fill the background with black
    g.fillAll(Colours::black);
    
    g.setColour (Colours::indianred);
    g.setFont (15.0f);
    g.drawFittedText ("Ring modulation at a fixed 800Hz frequency", getLocalBounds(), Justification::centred, 1);
}

void _2020sw2a2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
