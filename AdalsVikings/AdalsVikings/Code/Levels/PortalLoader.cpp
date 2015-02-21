#include "PortalLoader.h"

static std::map<PortalId, PortalPtr> mPortalMap;

PortalLoader::PortalLoader()
{
}

void PortalLoader::initialize()
{
	mPortalMap.clear();

	mPortalMap[Portal1] = PortalPtr(new Portal(sf::Vector2f(80, 1080), sf::Vector2f(0, 0), sf::Vector2f(200, 750), sf::Vector2f(0, 750)));
	mPortalMap[Portal2] = PortalPtr(new Portal(sf::Vector2f(80, 1080), sf::Vector2f(1840, 0), sf::Vector2f(1700, 750), sf::Vector2f(1900, 750)));
	
	//needed for first Portal
	mPortalMap[Portal1]->setGateway(&*mPortalMap[Portal2]);
	mPortalMap[Portal2]->setGateway(&*mPortalMap[Portal1]);
}

std::map<PortalId, PortalPtr> &PortalLoader::getPortals()
{
	return mPortalMap;
}

Portal &PortalLoader::getPortal(PortalId id)
{
	return *mPortalMap[id];
}