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
	Outside_ChurchToRoad,
	Outside_ChurchToChurch,
	ChurchToOutside_Church
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

