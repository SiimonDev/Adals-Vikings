#pragma once
namespace BoatEvent
{
	enum ID
	{
		StartDialogue,
		UlfrStartDialogue,
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
	static void initialize();
	static void triggerEvent(BoatEvent::ID event);
	static void handleEvent(BoatEvent::ID event);
	static void resetEvents();

	static bool hasBeenHandled(BoatEvent::ID event);
	static bool hasBeenTriggered(BoatEvent::ID event);

private:
	BoatEvents();
	BoatEvents(const BoatEvents&);
	void operator=(const BoatEvents&);
};