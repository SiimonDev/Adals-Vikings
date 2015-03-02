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
		mPortalMap[RoadToFarm] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(170, 220), sf::Vector2f(670, 440), sf::Vector2f(86, 650), sf::Vector2f(305, 686)));
		mPortalMap[FarmToRoad] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(170, 90), sf::Vector2f(1750, 640), sf::Vector2f(86, 680), sf::Vector2f(1920, 680)));
		mPortalMap[ForestRoadToCamp] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(137, 123), sf::Vector2f(1777, 673), sf::Vector2f(1854, 733), sf::Vector2f(1854, 733)));
		mPortalMap[CampToForestRoad] = PortalPtr(new Portal(LevelFolder::Camp_Clearing, sf::Vector2f(195, 120), sf::Vector2f(0, 600), sf::Vector2f(150, 630), sf::Vector2f(50, 630)));
		mPortalMap[Outside_ChurchToChurch] = PortalPtr(new Portal(LevelFolder::Church_Outside, sf::Vector2f(100, 230), sf::Vector2f(1270, 642), sf::Vector2f(1240, 870), sf::Vector2f(1240, 870)));
		mPortalMap[ChurchToOutside_Church] = PortalPtr(new Portal(LevelFolder::Church_Inside, sf::Vector2f(295, 399), sf::Vector2f(1400, 0), sf::Vector2f(1545, 358), sf::Vector2f(1545, 358)));
		mPortalMap[RoadToCamp] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(290, 270), sf::Vector2f(0, 450), sf::Vector2f(360, 691), sf::Vector2f(247, 676)));
		mPortalMap[CampToRoad] = PortalPtr(new Portal(LevelFolder::Camp_Clearing, sf::Vector2f(180, 170), sf::Vector2f(1450, 400), sf::Vector2f(1492, 595), sf::Vector2f(1540, 528)));
		mPortalMap[ForestRoadToForestCamp] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(290, 270), sf::Vector2f(0, 450), sf::Vector2f(360, 691), sf::Vector2f(247, 676)));
		mPortalMap[ForestCampToForestRoad] = PortalPtr(new Portal(LevelFolder::Forest_Camp, sf::Vector2f(180, 170), sf::Vector2f(1450, 400), sf::Vector2f(1492, 595), sf::Vector2f(1540, 528)));

		//connect the portals
		mPortalMap[BeachToRoad]->setGateway(&*mPortalMap[RoadToBeach]);
		mPortalMap[RoadToBeach]->setGateway(&*mPortalMap[BeachToRoad]);
		mPortalMap[RoadToOutside_Chuch]->setGateway(&*mPortalMap[Outside_ChurchToRoad]);
		mPortalMap[Outside_ChurchToRoad]->setGateway(&*mPortalMap[RoadToOutside_Chuch]);
		mPortalMap[RoadToFarm]->setGateway(&*mPortalMap[FarmToRoad]);
		mPortalMap[FarmToRoad]->setGateway(&*mPortalMap[RoadToFarm]);
		mPortalMap[Outside_ChurchToChurch]->setGateway(&*mPortalMap[ChurchToOutside_Church]);
		mPortalMap[ChurchToOutside_Church]->setGateway(&*mPortalMap[Outside_ChurchToChurch]);
		mPortalMap[RoadToCamp]->setGateway(&*mPortalMap[CampToRoad]);
		mPortalMap[CampToRoad]->setGateway(&*mPortalMap[RoadToCamp]);
		mPortalMap[ForestRoadToCamp]->setGateway(&*mPortalMap[CampToForestRoad]);
		mPortalMap[CampToForestRoad]->setGateway(&*mPortalMap[ForestRoadToCamp]);
		mPortalMap[ForestRoadToForestCamp]->setGateway(&*mPortalMap[ForestCampToForestRoad]);
		mPortalMap[ForestCampToForestRoad]->setGateway(&*mPortalMap[ForestRoadToForestCamp]);
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
