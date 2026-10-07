#pragma once
#include <JuceHeader.h>
#include "Formula.h"
class jAudioMathMIDIProcessor:public juce::AudioProcessor{
public:
 jAudioMathMIDIProcessor();~jAudioMathMIDIProcessor()override=default;
 void prepareToPlay(double,int)override;void releaseResources()override{};bool isBusesLayoutSupported(const BusesLayout&)const override{return true;}
 void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&)override;juce::AudioProcessorEditor*createEditor()override;bool hasEditor()const override{return true;}
 const juce::String getName()const override{return"jAudio Math MIDI";}bool acceptsMidi()const override{return true;}bool producesMidi()const override{return true;}bool isMidiEffect()const override{return true;}double getTailLengthSeconds()const override{return 0;}
 int getNumPrograms()override{return 1;}int getCurrentProgram()override{return 0;}void setCurrentProgram(int)override{}const juce::String getProgramName(int)override{return{};}void changeProgramName(int,const juce::String&)override{}
 void getStateInformation(juce::MemoryBlock&)override;void setStateInformation(const void*,int)override;
 void setFormula(const juce::String&s){formulaText=s;formula.set(s.toStdString());}juce::String getFormula()const{return formulaText;}
private:Formula formula;juce::String formulaText{"60 + round(sin(t*0.25)*7)"};double sr=44100;int lastNote=-1,step=0;float bpm=120,division=.25f,rangeMin=36,rangeMax=84,velocity=100,root=0;bool quantize=true;JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(jAudioMathMIDIProcessor)};
