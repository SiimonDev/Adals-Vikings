#pragma once
#include <string>

namespace BoatEvent
{
	enum ID
	{
		StartDialogue,
		UlfrStartDialogue,
		IntroScreen,
		PickedUpBucket,
		GivenBucketToLeifr,
		FluteFromAlfr,
		DroppedFluteOnBrynja,
		TalkedToBrandr,
		TalkedToValdis,
		GottenMap,
		GivenMapToBrandr,
		EVENT_SIZE
	};
}

class BoatEvents
{
public:
	static void initialize(std::string filePath = "");
	static void triggerEvent(BoatEvent::ID event);
	static void handleEvent(BoatEvent::ID event);
	static void saveEvents(std::string filePath);
	static void resetEvents();

	static bool hasBeenHandled(BoatEvent::ID event);
	static bool hasBeenTriggered(BoatEvent::ID event);

private:
	BoatEvents();
	BoatEvents(const BoatEvents&);
	void operator=(const BoatEvents&);
};