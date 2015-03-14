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
		mPortalMap[Ship1ToShip2] = PortalPtr(new Portal(LevelFolder::Ship_1, sf::Vector2f(110, 400), sf::Vector2f(0, 400), sf::Vector2f(200, 750), sf::Vector2f(0, 750)));
		mPortalMap[Ship1ToShip2]->setCursorRotation(-90);
		mPortalMap[Ship2ToShip1] = PortalPtr(new Portal(LevelFolder::Ship_2, sf::Vector2f(110, 400), sf::Vector2f(1810, 400), sf::Vector2f(1700, 750), sf::Vector2f(1900, 750)));
		mPortalMap[Ship2ToShip1]->setCursorRotation(90);

		//connect the portals
		mPortalMap[Ship1ToShip2]->setGateway(&*mPortalMap[Ship2ToShip1]);
		mPortalMap[Ship2ToShip1]->setGateway(&*mPortalMap[Ship1ToShip2]);
	}
	else if (LVLMI.getCurrentAct() == Act1)
	{
		mPortalMap[BeachToRoad] = PortalPtr(new Portal(LevelFolder::Beach, sf::Vector2f(150, 150), sf::Vector2f(0, 350), sf::Vector2f(170, 500), sf::Vector2f(0, 460)));
		mPortalMap[BeachToRoad]->setCursorRotation(-90);

		mPortalMap[RoadToBeach] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(550, 100), sf::Vector2f(50, 980), sf::Vector2f(460, 950), sf::Vector2f(360, 1079)));
		mPortalMap[RoadToBeach]->setCursorRotation(-135);

		mPortalMap[RoadToOutside_Chuch] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(400, 100), sf::Vector2f(1200, 980), sf::Vector2f(1260, 970), sf::Vector2f(1400, 1079)));
		mPortalMap[RoadToOutside_Chuch]->setCursorRotation(135);

		mPortalMap[Outside_ChurchToRoad] = PortalPtr(new Portal(LevelFolder::Church_Outside, sf::Vector2f(650, 50), sf::Vector2f(0, 1030), sf::Vector2f(515, 1005), sf::Vector2f(365, 1079)));
		mPortalMap[Outside_ChurchToRoad]->setCursorRotation(-135);

		mPortalMap[RoadToFarm] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(135, 140), sf::Vector2f(725, 470), sf::Vector2f(86, 650), sf::Vector2f(305, 686)));
		mPortalMap[RoadToFarm]->setCursorRotation(45);

		mPortalMap[FarmToRoad] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(170, 90), sf::Vector2f(1750, 640), sf::Vector2f(86, 680), sf::Vector2f(1920, 680)));
		mPortalMap[FarmToRoad]->setCursorRotation(-90);

		mPortalMap[ForestRoadToCamp] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(137, 123), sf::Vector2f(1777, 673), sf::Vector2f(1854, 733), sf::Vector2f(1854, 733)));
		mPortalMap[ForestRoadToCamp]->setCursorRotation(90);

		mPortalMap[CampToForestRoad] = PortalPtr(new Portal(LevelFolder::Camp_Clearing, sf::Vector2f(195, 120), sf::Vector2f(0, 600), sf::Vector2f(150, 630), sf::Vector2f(50, 630)));
		mPortalMap[CampToForestRoad]->setCursorRotation(-90);

		mPortalMap[Outside_ChurchToChurch] = PortalPtr(new Portal(LevelFolder::Church_Outside, sf::Vector2f(100, 230), sf::Vector2f(1270, 642), sf::Vector2f(1240, 870), sf::Vector2f(1240, 870)));
		mPortalMap[Outside_ChurchToChurch]->setCursorRotation(45);

		mPortalMap[ChurchToOutside_Church] = PortalPtr(new Portal(LevelFolder::Church_Inside, sf::Vector2f(295, 399), sf::Vector2f(1400, 0), sf::Vector2f(1545, 358), sf::Vector2f(1545, 358)));
		mPortalMap[ChurchToOutside_Church]->setCursorRotation(45);

		mPortalMap[RoadToCamp] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(290, 200), sf::Vector2f(0, 490), sf::Vector2f(360, 691), sf::Vector2f(247, 676)));
		mPortalMap[RoadToCamp]->setCursorRotation(-90);

		mPortalMap[CampToRoad] = PortalPtr(new Portal(LevelFolder::Camp_Clearing, sf::Vector2f(180, 170), sf::Vector2f(1450, 400), sf::Vector2f(1492, 595), sf::Vector2f(1540, 528)));
		mPortalMap[CampToRoad]->setCursorRotation(45);

		mPortalMap[ForestRoadToForestCamp] = PortalPtr(new Portal(LevelFolder::Forest_Road, sf::Vector2f(290, 270), sf::Vector2f(0, 550), sf::Vector2f(360, 691), sf::Vector2f(247, 676)));
		mPortalMap[ForestRoadToForestCamp]->setCursorRotation(-90);
		
		mPortalMap[ForestCampToForestRoad] = PortalPtr(new Portal(LevelFolder::Forest_Camp, sf::Vector2f(240, 370), sf::Vector2f(1680, 470), sf::Vector2f(1870, 690), sf::Vector2f(1920, 690)));
		mPortalMap[ForestCampToForestRoad]->setCursorRotation(90);

		mPortalMap[BeachToTavernOutside] = PortalPtr(new Portal(LevelFolder::Beach, sf::Vector2f(410, 290), sf::Vector2f(1360, 0), sf::Vector2f(1480, 290), sf::Vector2f(1460, 185)));
		mPortalMap[BeachToTavernOutside]->setCursorRotation(45);
		
		mPortalMap[TavernOutsideToBeach] = PortalPtr(new Portal(LevelFolder::Tavern_Outside, sf::Vector2f(100, 1080), sf::Vector2f(0, 0), sf::Vector2f(100, 1065), sf::Vector2f(0, 1065)));
		mPortalMap[TavernOutsideToBeach]->setCursorRotation(-90);
		
		mPortalMap[TavernOutsideToTavernInside] = PortalPtr(new Portal(LevelFolder::Tavern_Outside, sf::Vector2f(130, 300), sf::Vector2f(930, 600), sf::Vector2f(975, 885), sf::Vector2f(975, 885)));
		mPortalMap[TavernOutsideToTavernInside]->setCursorRotation(0);
		
		mPortalMap[TavernInsideToTavernOutside] = PortalPtr(new Portal(LevelFolder::Tavern_Inside, sf::Vector2f(250, 705), sf::Vector2f(0, 235), sf::Vector2f(220, 945), sf::Vector2f(220, 945)));
		mPortalMap[TavernInsideToTavernOutside]->setCursorRotation(-90);
		
		mPortalMap[CampClearingToCamPFinished] = PortalPtr(new Portal(LevelFolder::Camp_Clearing, sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
		mPortalMap[CampClearingToCamPFinished]->setCursorRotation(0);
		
		mPortalMap[CampFinishedToCampClearing] = PortalPtr(new Portal(LevelFolder::Camp_Finished, sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
		mPortalMap[CampFinishedToCampClearing]->setCursorRotation(0);

		mPortalMap[CampFinishedToRoad] = PortalPtr(new Portal(LevelFolder::Camp_Finished, sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
		mPortalMap[CampFinishedToRoad]->setCursorRotation(45);
		
		mPortalMap[RoadToCampFinished] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(290, 270), sf::Vector2f(0, 450), sf::Vector2f(360, 691), sf::Vector2f(247, 676)));
		mPortalMap[RoadToCampFinished]->setCursorRotation(-90);

		mPortalMap[RoadToGates] = PortalPtr(new Portal(LevelFolder::Road, sf::Vector2f(240, 100), sf::Vector2f(1680, 560), sf::Vector2f(1815, 605), sf::Vector2f(1915, 600)));
		mPortalMap[RoadToGates]->setCursorRotation(90);

		mPortalMap[GatesToRoad] = PortalPtr(new Portal(LevelFolder::City_Gates, sf::Vector2f(420, 175), sf::Vector2f(0, 905), sf::Vector2f(185, 970), sf::Vector2f(20, 1050)));
		mPortalMap[GatesToRoad]->setCursorRotation(-90);

		mPortalMap[GatesToCliffs] = PortalPtr(new Portal(LevelFolder::City_Gates, sf::Vector2f(255, 170), sf::Vector2f(1100, 910), sf::Vector2f(1190, 990), sf::Vector2f(1220, 1075)));
		mPortalMap[GatesToCliffs]->setCursorRotation(90);

		mPortalMap[CliffsToGates] = PortalPtr(new Portal(LevelFolder::Cliffs_Up, sf::Vector2f(80, 430), sf::Vector2f(0, 250), sf::Vector2f(120, 525), sf::Vector2f(5, 525)));
		mPortalMap[CliffsToGates]->setCursorRotation(-90);

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
		mPortalMap[BeachToTavernOutside]->setGateway(&*mPortalMap[TavernOutsideToBeach]);
		mPortalMap[TavernOutsideToBeach]->setGateway(&*mPortalMap[BeachToTavernOutside]);
		mPortalMap[TavernOutsideToTavernInside]->setGateway(&*mPortalMap[TavernInsideToTavernOutside]);
		mPortalMap[TavernInsideToTavernOutside]->setGateway(&*mPortalMap[TavernOutsideToTavernInside]);
		mPortalMap[CampClearingToCamPFinished]->setGateway(&*mPortalMap[CampFinishedToCampClearing]);
		mPortalMap[CampFinishedToCampClearing]->setGateway(&*mPortalMap[CampClearingToCamPFinished]);
		mPortalMap[RoadToCampFinished]->setGateway(&*mPortalMap[CampFinishedToRoad]);
		mPortalMap[CampFinishedToRoad]->setGateway(&*mPortalMap[RoadToCampFinished]);
		mPortalMap[RoadToGates]->setGateway(&*mPortalMap[GatesToRoad]);
		mPortalMap[GatesToRoad]->setGateway(&*mPortalMap[RoadToGates]);

		mPortalMap[GatesToCliffs]->setGateway(&*mPortalMap[CliffsToGates]);
		mPortalMap[CliffsToGates]->setGateway(&*mPortalMap[GatesToCliffs]);
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
