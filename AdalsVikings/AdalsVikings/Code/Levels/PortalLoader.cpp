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
		mPortalMap[Ship1ToShip2] = PortalPtr(new Portal(sf::Vector2f(110, 1080), sf::Vector2f(0, 0), sf::Vector2f(200, 750), sf::Vector2f(0, 750)));
		mPortalMap[Ship2ToShip1] = PortalPtr(new Portal(sf::Vector2f(110, 1080), sf::Vector2f(1790, 0), sf::Vector2f(1700, 750), sf::Vector2f(1900, 750), &*mPortalMap[Ship1ToShip2]));

		//needed for first Portal
		mPortalMap[Ship1ToShip2]->setGateway(&*mPortalMap[Ship2ToShip1]);
	}
	else if (LVLMI.getCurrentAct() == Act1)
	{
		mPortalMap[BeachToRoad] = PortalPtr(new Portal(sf::Vector2f(150, 150), sf::Vector2f(0, 350), sf::Vector2f(230, 350), sf::Vector2f(200, 250)));
		mPortalMap[RoadToBeach] = PortalPtr(new Portal(sf::Vector2f(150, 150), sf::Vector2f(350, 900), sf::Vector2f(400, 900), sf::Vector2f(400, 1000), &*mPortalMap[BeachToRoad]));
		//mPortalMap[RoadToOutside_Chuch] = PortalPtr(new Portal(sf::Vector2f(200, 200), sf::Vector2f(350, 900), sf::Vector2f(400, 900), sf::Vector2f(400, 1000), &*mPortalMap[BeachToRoad]));
		//needed for first Portal
		mPortalMap[BeachToRoad]->setGateway(&*mPortalMap[RoadToBeach]);
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
	{
		it->second->unload();
	}
	mPortalMap.clear();
}
