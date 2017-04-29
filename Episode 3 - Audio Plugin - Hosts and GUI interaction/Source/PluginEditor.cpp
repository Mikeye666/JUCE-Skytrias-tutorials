#include "PluginProcessor.h"
#include "PluginEditor.h"

Tutorial3pluginAudioProcessorEditor::Tutorial3pluginAudioProcessorEditor (Tutorial3pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	addAndMakeVisible(volumeSlider);
	volumeSlider->setRange(0.0, 1.0, 0.001);
	volumeSlider->addListener(this);

    setSize (400, 300);
}

Tutorial3pluginAudioProcessorEditor::~Tutorial3pluginAudioProcessorEditor()
{

}

//==============================================================================
void Tutorial3pluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void Tutorial3pluginAudioProcessorEditor::resized()
{
	Rectangle<int> r = getLocalBounds();
	volumeSlider->setBounds(r);
}

void Tutorial3pluginAudioProcessorEditor::sliderValueChanged(Slider* sliderToCheck)
{
	if (sliderToCheck == volumeSlider)
	{
		processor.level = volumeSlider->getValue();
	}
}
