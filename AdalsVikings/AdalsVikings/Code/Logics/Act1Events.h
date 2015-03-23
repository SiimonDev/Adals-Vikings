#pragma once
#include <string>

namespace Act1Event
{
	enum ID
	{
		Beach_Intro,
		Beach_Alfr,
		Beach_Dagny,
		Beach_Finnr,
		Beach_Leifr,
		Beach_Yngvarr,
		Beach_Valdis,
		Beach_Ending,
		Enter_Road,
		Road_StartMailmanConv,
		Road_GiveMailmanPaper,
		ChurchOutside_TalkToPrincess,
		ChurchInside_GoBackDialogue,
		CampClearing_Brynja,
		CampClearing_Valdis,
		CampClearing_Leifr,
		CampClearing_TalkedToAll,
		TavernInside_GetAxeHead,
		TavernInside_GiveAxeToBrandr,
		ForestCamp_NeedFireQuest,
		GotBeerDeerPelt,
		ForestCamp_BeerDeer,
		LightCampFire,
		CampFinished_Conversation,
		ForestCampFire,
		AfterCampRoad_Conversation,
		TalkedToGuard,
		CliffsMonologue,
		Ruins_Introduction,
		Ruins_RockSlide,
		GotCandleLight,
		TooDarkToGo,
		TalkedToJacob,
		TalkedToParrik,
		SolvedConflict,
		GivenFlowerToValdis,
		GivenMeadToValdis,
		GivenSleepingMeatToWolf,
		GivenSkullToMiner,
		MinedSomeGold,
		GivenSkullHelmetToGuard,
		SweetGold,
		PickupMeat,
		ForestRoadConver,
		FlowerActive,
		EVENT_SIZE
	};
}

class Act1Events
{
public:
	static void initialize(std::string filePath = "");
	static void triggerEvent(Act1Event::ID event);
	static void handleEvent(Act1Event::ID event);
	static void saveEvents(std::string filePath);
	static void resetEvents();

	static bool hasBeenHandled(Act1Event::ID event);
	static bool hasBeenTriggered(Act1Event::ID event);

private:
	Act1Events();
	Act1Events(const Act1Events&);
	void operator=(const Act1Events&);
};

