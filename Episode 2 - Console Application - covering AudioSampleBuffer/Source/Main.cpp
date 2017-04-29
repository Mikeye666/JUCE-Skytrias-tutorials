#include "../JuceLibraryCode/JuceHeader.h"

void main ()
{
	AudioSampleBuffer buffer{ 2, 10 };

	float* writeBuffer = buffer.getWritePointer(0);
	for (auto i = 0; i < buffer.getNumSamples(); ++i)
		writeBuffer[i] = (Random().nextFloat() * 2 - 1) * 0.1;

	const float* readBuffer = buffer.getReadPointer(0);
	for (auto i = 0; i < buffer.getNumSamples(); ++i)
		Logger::writeToLog(String(readBuffer[i]));

	while (1) {}
}
