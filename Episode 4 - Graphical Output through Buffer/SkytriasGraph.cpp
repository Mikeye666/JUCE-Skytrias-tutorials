#include "SkytriasGraph.h"

SkytriasGraph::SkytriasGraph()
{
	setOpaque(true);
	startTimerHz(60);
}

SkytriasGraph::~SkytriasGraph()
{
}

/*own methods*/
void SkytriasGraph::pushBuffer(const AudioSourceChannelInfo& newBuffer)
{
	levels = Array<float>(newBuffer.buffer->getReadPointer(0, newBuffer.startSample), newBuffer.numSamples);
}

void SkytriasGraph::setColours(Colour newBackgroundColour, Colour newWaveformColour)
{
	backgroundColour = newBackgroundColour;
	waveformColour = newWaveformColour;
}

void SkytriasGraph::setRepaintRate(int newFrequencyHz)
{
	startTimerHz(newFrequencyHz);
}

/*overriders*/
void SkytriasGraph::paint(Graphics& g)
{
	g.fillAll(backgroundColour);
	g.setColour(waveformColour);

	float height = getHeight() / 2;
	float amplitude = 100.0f;
	float rectWidth = 4.0f;

	for (float i = 0; i < getWidth() / 2; ++i)
		g.fillRect(i * rectWidth, height + -levels.getUnchecked(i) * amplitude, 
				   rectWidth, rectWidth);
}

void SkytriasGraph::timerCallback()
{
	repaint();
}

