#pragma once
#include "Portal.h"
#include <map>

typedef std::unique_ptr<Portal> PortalPtr;

enum PortalId
{
	Ship1ToShip2,
	Ship2ToShip1,
	BeachToRoad,
	BeachToBeachHill,
	BeachToHill,
	RoadToBeach,
	RoadToOutside_Chuch,
	RoadToFarm,
	FarmToRoad,
	Farm1ToFarm2,
	Farm2ToFarm1,
	RoadToGates,
	GatesToRoad,
	CampToForestRoad,
	ForestRoadToCamp,
	ForestCampToForestRoad,
	ForestRoadToForestCamp,
	ForestCampToRoad,
	Outside_ChurchToRoad,
	Outside_ChurchToChurch,
	ChurchToOutside_Church,
	RoadToCamp,
	CampToRoad,
	BeachToTavernOutside,
	TavernOutsideToBeach,
	TavernOutsideToTavernInside,
	TavernInsideToTavernOutside,
	CampFinishedToCampClearing,
	CampClearingToCamPFinished,
	CampFinishedToRoad,
	RoadToCampFinished,
	GatesToCliffs,
	CliffsToGates,
	CliffsToRuins,
	RuinsToCliffs
};
class PortalLoader
{
public:
	static void load();
	static void unload();

	static std::map<PortalId, PortalPtr> &getPortals();
	static Portal &getPortal(PortalId id);

private:
	PortalLoader();
	PortalLoader(PortalLoader&);
	void operator=(PortalLoader&);
};

