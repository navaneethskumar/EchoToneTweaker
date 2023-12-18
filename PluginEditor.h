/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class EchoToneTweakerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EchoToneTweakerAudioProcessorEditor (EchoToneTweakerAudioProcessor&);
    ~EchoToneTweakerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EchoToneTweakerAudioProcessor& audioProcessor;
    juce::Slider feedbackSlider;
    juce::Label feedbackLabel;
    juce::Slider delayTimeKnob;
    juce::Label delayTimeLabel;
    juce::Slider dryWetKnob;
    juce::Label dryWetLabel;

    juce::Slider eqFcenterKnob;
    juce::Label eqFcenterLabel;

    juce::Slider eqQKnob;
    juce::Label eqQKnobLabel;

    juce::Slider eqGainKnob;
    juce::Label eqGainKnobLabel;

    juce::Slider outputGainSlider;
    juce::Label outputGainLabel;
    //declaring parameters here
    juce::AudioParameterFloat* feedbackSliderParameter;
    juce::AudioParameterFloat* delayTimeKnobParameter;
    juce::AudioParameterFloat* dryWetKnobParameter;

    juce::AudioParameterFloat* eqFcenterKnobParameter;
    juce::AudioParameterFloat* eqQKnobParameter;
    juce::AudioParameterFloat* eqGainKnobParameter;

    juce::AudioParameterFloat* outputGainParameter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EchoToneTweakerAudioProcessorEditor)
};
