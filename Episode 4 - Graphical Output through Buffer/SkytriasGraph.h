#pragma once

#include "JuceHeader.h"

class SkytriasGraph : public Component, Timer
{
public:
	SkytriasGraph();
	~SkytriasGraph();

	/*own methods*/
	void pushBuffer(const AudioSourceChannelInfo& newBuffer);
	void setColours(Colour backgroundColour, Colour waveformColour);
	void setRepaintRate(int newFrequencyHz);

	/*overriders*/
	void paint(Graphics& g) override;
	void timerCallback() override;

private:
	Array<float> levels;
	Colour backgroundColour = Colours::white;
	Colour waveformColour = Colours::black;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkytriasGraph)
};
