#include "PortalLoader.h"


PortalLoader::PortalLoader()
{
	load();
}


PortalLoader::~PortalLoader()
{
}

void PortalLoader::load()
{
	Portal TestPortal1(sf::Vector2f(50, 1080), sf::Vector2f(500, 0));
	Portal TestPortal2(sf::Vector2f(30, 30), sf::Vector2f(0, 700));

	mPortalMap.insert(std::make_pair(Portal1, std::move(TestPortal1)));
	mPortalMap.insert(std::make_pair(Portal2, std::move(TestPortal2)));
	
	auto found = mPortalMap.find(Portal1);
	auto found1 = mPortalMap.find(Portal2);
	found->second.setGateway(&found1->second);

}
Portal& PortalLoader::getPortal(PortalId id)
{
	auto found = mPortalMap.find(id);
	return found->second;
}