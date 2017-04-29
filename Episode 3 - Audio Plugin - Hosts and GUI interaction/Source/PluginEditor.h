#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Tutorial3pluginAudioProcessorEditor  : public AudioProcessorEditor, Slider::Listener
{
public:
    Tutorial3pluginAudioProcessorEditor (Tutorial3pluginAudioProcessor&);
    ~Tutorial3pluginAudioProcessorEditor();

    void paint (Graphics&) override;
	void resized() override;
	void sliderValueChanged(Slider* sliderToCheck) override;

private:
    Tutorial3pluginAudioProcessor& processor;
	ScopedPointer<Slider> volumeSlider = new Slider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Tutorial3pluginAudioProcessorEditor)
};
