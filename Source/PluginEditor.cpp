#include "PluginEditor.h"

VoxAnchorAudioProcessorEditor::VoxAnchorAudioProcessorEditor (VoxAnchorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), tooltipWindow (this, 700)
{
    setResizable (true, true);
    setResizeLimits (960, 640, 1920, 1200);

    timeSlider.setSliderStyle (juce::Slider::LinearVertical);
    timeSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 64, 20);
    timeSlider.setTooltip ("Time Tightness: higher values lock timing closer to the reference. 0 = no timing correction.");
    addAndMakeVisible (timeSlider);

    setSize (960, 640);
}

VoxAnchorAudioProcessorEditor::~VoxAnchorAudioProcessorEditor() {}

void VoxAnchorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff0b1020));
}

void VoxAnchorAudioProcessorEditor::resized()
{
    timeSlider.setBounds (40, 40, 60, getHeight() - 80);
}
