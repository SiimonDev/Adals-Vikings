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
		mPortalMap[Portal1] = PortalPtr(new Portal(sf::Vector2f(80, 1080), sf::Vector2f(0, 0), sf::Vector2f(200, 750), sf::Vector2f(0, 750)));
		mPortalMap[Portal2] = PortalPtr(new Portal(sf::Vector2f(80, 1080), sf::Vector2f(1840, 0), sf::Vector2f(1700, 750), sf::Vector2f(1900, 750)));

		//needed for first Portal
		mPortalMap[Portal1]->setGateway(&*mPortalMap[Portal2]);
		mPortalMap[Portal2]->setGateway(&*mPortalMap[Portal1]);
	}
	else if (LVLMI.getCurrentAct() == Act1)
	{
		mPortalMap[Portal3] = PortalPtr(new Portal(sf::Vector2f(80, 1080), sf::Vector2f(800, 0), sf::Vector2f(200, 750), sf::Vector2f(0, 750)));
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
