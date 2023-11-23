/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef VASTAUDIOPROCESSOREDITOR_H_INCLUDED
#define VASTAUDIOPROCESSOREDITOR_H_INCLUDED

#include "../Engine/VASTEngineHeader.h"
#include "VASTAudioProcessor.h"
#include "VASTVaporizerComponent.h"
#include "VASTUtils/VASTLookAndFeel.h"

//==============================================================================
/**
*/
static atomic<bool> b_ap_alive;

class VASTAudioProcessorEditor : public AudioProcessorEditor, MultiTimer
{
public:
    VASTAudioProcessorEditor (VASTAudioProcessor&);
    ~VASTAudioProcessorEditor();

    //==============================================================================
	void resized() override;
	void paint(Graphics& g) override;
	void timerCallback(int timerID) override;
	
	//==============================================================================
	VASTAudioProcessor* getProcessor();
    std::unique_ptr<VASTVaporizerComponent> vaporizerComponent;
	
	juce::Array<Component*> m_VASTComponentsAll;

	//const int m_iMinWidth = 800;
	//const int m_iMinHeight = 450;
	const int m_iMinWidth = 425;
	const int m_iMinHeight = 300;
	int m_iMaxWidth = 3550;
	int m_iMaxHeight = 2000;

	void startPaintingToImage();
	void endPaintingToImage();

	void initAllLookAndFeels();
	void setActiveLookAndFeel(int no);
	VASTLookAndFeel* getCurrentVASTLookAndFeel();
	Component* findChildComponetWithName(Component* parent, String compName);

	class VASTComponentBoundsConstrainer : public ComponentBoundsConstrainer {
	public:
		VASTAudioProcessorEditor* myEditor;
		bool isBeingCornerResized = false;
		VASTComponentBoundsConstrainer(VASTAudioProcessorEditor* editor) {
			myEditor = editor;
		};

		void resizeStart() override {
			myEditor->startPaintingToImage();
			isBeingCornerResized = true;
		};
		void resizeEnd() override {
			myEditor->endPaintingToImage();
			isBeingCornerResized = false;
			myEditor->resized();
		};
	};

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VASTAudioProcessor& processor;

	TooltipWindow tooltipWindow{ this, 200 }; //just add and leave here
    std::unique_ptr<juce::AlertWindow> m_alertWindow;

	bool resizeCalledFromConstructor = false;
	void showNewerVersionPopup();

#if !defined JUCE_LINUX
	VASTComponentBoundsConstrainer m_componentBoundsConstrainer = { this };
#endif

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VASTAudioProcessorEditor)
};

#endif
