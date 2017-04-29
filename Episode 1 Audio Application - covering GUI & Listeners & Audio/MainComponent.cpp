#include "../JuceLibraryCode/JuceHeader.h"

class MainContentComponent   : public AudioAppComponent, Slider::Listener, Button::Listener
{
public:
    //==============================================================================
    MainContentComponent()
    {
		addAndMakeVisible(volumeSlider);
		volumeSlider.setRange(0.0, 0.01, 0.0001);
		volumeSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::crimson);
		volumeSlider.addListener(this);

		addAndMakeVisible(helloWorld);
		helloWorld.addListener(this);

		setSize (800, 600);
        setAudioChannels (0, 2);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {

    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
		for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
		{
			float* buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
		
			for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				buffer[sample] = (Random().nextFloat() * 2 - 1) * level;
			}
		}
    }

    void releaseResources() override
    {

    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

		g.setColour(Colours::crimson);
		g.fillRect(100, 100, 100, 100);
    }

    void resized() override
    {
		volumeSlider.setBounds(0, 0, 500, 100);
		helloWorld.setBounds(250, 250, 250, 250);
    }

	void sliderValueChanged(Slider* slider) override
	{
		if (slider == &volumeSlider)
		{
			level = volumeSlider.getValue();
		}
	}

	void buttonClicked(Button* button) override
	{
		if (button == &helloWorld)
		{
			Logger::writeToLog("helloWorld!");
		}
	}

private:
	Slider volumeSlider{ Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox };
	TextButton helloWorld{ "vst" };
	double level = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
