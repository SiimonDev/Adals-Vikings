#include "PortalLoader.h"
#include "LevelManager.h"

static std::map<PortalId, PortalPtr> mPortalMap;

PortalLoader::PortalLoader()
{
}

void PortalLoader::load()
{
	if (mPortalMap.size() != 0)
		mPortalMap.clear();

	if (LVLMI.getCurrentAct() == Ship)
	{
		mPortalMap[Ship1ToShip2] = PortalPtr(new Portal(LevelFolder::Ship_1, sf::Vector2f(110, 1080), sf::Vector2f(0, 0), sf::Vector2f(200, 750), sf::Vector2f(0, 750)));
		mPortalMap[Ship2ToShip1] = PortalPtr(new Portal(LevelFolder::Ship_2, sf::Vector2f(110, 1080), sf::Vector2f(1790, 0), sf::Vector2f(1700, 750), sf::Vector2f(1900, 750)));

		//needed for first Portal
		mPortalMap[Ship1ToShip2]->setGateway(&*mPortalMap[Ship2ToShip1]);
		mPortalMap[Ship2ToShip1]->setGateway(&*mPortalMap[Ship1ToShip2]);
	}
	else if (LVLMI.getCurrentAct() == Act1)
	{
		mPortalMap[BeachToRoad] = PortalPtr(new Portal(LevelFolder::Beach, sf::Vector2f(150, 150), sf::Vector2f(0, 350), sf::Vector2f(170, 500), sf::Vector2f(0, 460)));
		mPortalMap[RoadToBeach] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(550, 100), sf::Vector2f(50, 980), sf::Vector2f(460, 950), sf::Vector2f(360, 1079)));
		mPortalMap[RoadToOutside_Chuch] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(400, 100), sf::Vector2f(1200, 980), sf::Vector2f(1260, 970), sf::Vector2f(1400, 1079)));
		mPortalMap[Outside_ChurchToRoad] = PortalPtr(new Portal(LevelFolder::Church_Outside, sf::Vector2f(650, 50), sf::Vector2f(0, 1030), sf::Vector2f(515, 1005), sf::Vector2f(365, 1079)));
		mPortalMap[RoadToForestCamp] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(240, 70), sf::Vector2f(50, 630), sf::Vector2f(86, 650), sf::Vector2f(305, 686)));
		mPortalMap[ForestCampToRoad] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(170, 90), sf::Vector2f(1750, 640), sf::Vector2f(86, 680), sf::Vector2f(1920, 680)));
		mPortalMap[Outside_ChurchToChurch] = PortalPtr(new Portal(LevelFolder::Church_Outside, sf::Vector2f(100, 230), sf::Vector2f(1270, 642), sf::Vector2f(1240, 870), sf::Vector2f(1240, 870)));
		mPortalMap[ChurchToOutside_Church] = PortalPtr(new Portal(LevelFolder::Church_Inside, sf::Vector2f(295, 399), sf::Vector2f(1400, 0), sf::Vector2f(1545, 358), sf::Vector2f(1545, 358)));
		mPortalMap[RoadToCamp] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(100, 200), sf::Vector2f(680, 480), sf::Vector2f(1240, 870), sf::Vector2f(1240, 870)));
		mPortalMap[CampToRoad] = PortalPtr(new Portal(LevelFolder::Camp_Clearing, sf::Vector2f(295, 399), sf::Vector2f(1400, 0), sf::Vector2f(1545, 358), sf::Vector2f(1545, 358)));

		//connect the portals
		mPortalMap[BeachToRoad]->setGateway(&*mPortalMap[RoadToBeach]);
		mPortalMap[RoadToBeach]->setGateway(&*mPortalMap[BeachToRoad]);
		mPortalMap[RoadToOutside_Chuch]->setGateway(&*mPortalMap[Outside_ChurchToRoad]);
		mPortalMap[Outside_ChurchToRoad]->setGateway(&*mPortalMap[RoadToOutside_Chuch]);
		mPortalMap[RoadToForestRoad]->setGateway(&*mPortalMap[ForestCampToRoad]);
		mPortalMap[ForestCampToRoad]->setGateway(&*mPortalMap[RoadToForestRoad]);
		mPortalMap[Outside_ChurchToChurch]->setGateway(&*mPortalMap[ChurchToOutside_Church]);
		mPortalMap[ChurchToOutside_Church]->setGateway(&*mPortalMap[Outside_ChurchToChurch]);
		mPortalMap[RoadToCamp]->setGateway(&*mPortalMap[CampToRoad]);
		mPortalMap[CampToRoad]->setGateway(&*mPortalMap[RoadToCamp]);
	}
}

std::map<PortalId, PortalPtr> &PortalLoader::getPortals()
{
	return mPortalMap;
}

Portal &PortalLoader::getPortal(PortalId id)
{
	return *mPortalMap[id];
}

void PortalLoader::unload()
{
	for (std::map<PortalId, PortalPtr>::const_iterator it = mPortalMap.begin(); it != mPortalMap.end(); it++)
		it->second->unload();
	mPortalMap.clear();
}
