#pragma once
#include "Portal.h"
#include <map>

enum PortalId
{
	Portal1,
	Portal2
};
class PortalLoader
{
public:
	PortalLoader();
	~PortalLoader();

	void load();
	Portal& getPortal(PortalId id);

private:
	//std::vector<Portal> mPortalVector;
	std::map<PortalId, Portal> mPortalMap;
};

