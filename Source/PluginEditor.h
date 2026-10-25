#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class VoxAnchorAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    VoxAnchorAudioProcessorEditor (VoxAnchorAudioProcessor&);
    ~VoxAnchorAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    VoxAnchorAudioProcessor& audioProcessor;
    juce::Slider timeSlider;
    juce::TooltipWindow tooltipWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoxAnchorAudioProcessorEditor)
};
