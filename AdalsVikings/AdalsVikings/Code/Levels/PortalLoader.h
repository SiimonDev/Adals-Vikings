#pragma once
#include "Portal.h"
#include <map>

typedef std::unique_ptr<Portal> PortalPtr;

enum PortalId
{
	Portal1,
	Portal2,
	Portal3,
	durr,
	PortalToBoat
};
class PortalLoader
{
public:
	static void initialize();

	static std::map<PortalId, PortalPtr> &getPortals();
	static Portal &getPortal(PortalId id);

private:
	PortalLoader();
	PortalLoader(PortalLoader&);
	void operator=(PortalLoader&);
};

