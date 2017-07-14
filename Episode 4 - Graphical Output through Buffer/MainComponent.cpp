#include "../JuceLibraryCode/JuceHeader.h"
#include "SkytriasGraph.h"

class MainContentComponent   : public AudioAppComponent, Slider::Listener
{
public:
    MainContentComponent()
    {
		addAndMakeVisible(graph);
		//graph.setColours(Colours::lightgrey, Colours::crimson);

		addAndMakeVisible(avc);

		addAndMakeVisible(volumeSlider);
		volumeSlider.setRange(0.0, 1.0, 0.001);
		volumeSlider.addListener(this);

        setSize (600, 200);
        setAudioChannels (0, 2);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
		expectedSampleRate = sampleRate;
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
		for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			currentAngle = 0;
			float* const writeBuffer = bufferToFill.buffer->getWritePointer(channel);

			for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				writeBuffer[sample] = (sinf(currentAngle) * level);
				currentAngle += (2 * double_Pi * pitch / expectedSampleRate);
			}
		}

		graph.pushBuffer(bufferToFill);
		//avc.pushBuffer(bufferToFill);
    }

    void releaseResources() override { }

    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	}

    void resized() override
    {
		auto r = getLocalBounds();
		volumeSlider.setBounds(r.removeFromLeft(200));
		graph.setBounds(r);
		//avc.setBounds(r);
    }

	/*listeners*/
	void sliderValueChanged(Slider* slider) override
	{
		if (slider == &volumeSlider)
			level = volumeSlider.getValue();
	}

private:
	SkytriasGraph graph;
	AudioVisualiserComponent avc{ 2 };

	Slider volumeSlider{Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox};
	double expectedSampleRate, currentAngle = 0, level = 0.0, pitch = 440;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
