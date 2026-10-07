#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
class jAudioMathMIDIEditor:public juce::AudioProcessorEditor{
public:jAudioMathMIDIEditor(jAudioMathMIDIProcessor&);void paint(juce::Graphics&)override;void resized()override;
private:jAudioMathMIDIProcessor&p;juce::Label logo;juce::TextEditor formula;juce::TextButton apply;JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jAudioMathMIDIEditor)};