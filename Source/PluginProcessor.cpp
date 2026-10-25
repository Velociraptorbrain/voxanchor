#include "PluginProcessor.h"
#include "PluginEditor.h"

VoxAnchorAudioProcessor::VoxAnchorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                     .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
#endif
{
}

VoxAnchorAudioProcessor::~VoxAnchorAudioProcessor() {}

const juce::String VoxAnchorAudioProcessor::getName() const { return JucePlugin_Name; }
bool VoxAnchorAudioProcessor::acceptsMidi() const { return false; }
bool VoxAnchorAudioProcessor::producesMidi() const { return false; }
bool VoxAnchorAudioProcessor::isMidiEffect() const { return false; }
double VoxAnchorAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int VoxAnchorAudioProcessor::getNumPrograms() { return 1; }
int VoxAnchorAudioProcessor::getCurrentProgram() { return 0; }
void VoxAnchorAudioProcessor::setCurrentProgram (int index) { juce::ignoreUnused (index); }
const juce::String VoxAnchorAudioProcessor::getProgramName (int index) { juce::ignoreUnused (index); return {}; }
void VoxAnchorAudioProcessor::changeProgramName (int index, const juce::String& newName) { juce::ignoreUnused (index, newName); }

void VoxAnchorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) { juce::ignoreUnused (sampleRate, samplesPerBlock); }
void VoxAnchorAudioProcessor::releaseResources() {}
void VoxAnchorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) { juce::ignoreUnused (midiMessages); juce::ScopedNoDenormals noDenormals; }

bool VoxAnchorAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* VoxAnchorAudioProcessor::createEditor() { return new VoxAnchorAudioProcessorEditor (*this); }

void VoxAnchorAudioProcessor::getStateInformation (juce::MemoryBlock& destData) { juce::ignoreUnused (destData); }
void VoxAnchorAudioProcessor::setStateInformation (const void* data, int sizeInBytes) { juce::ignoreUnused (data, sizeInBytes); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new VoxAnchorAudioProcessor(); }
