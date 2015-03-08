#pragma once
#include "NPC.h"
#include <map>
#include <memory>

typedef std::unique_ptr<Npc> NpcPtr;

#define NpcHandlerI NpcHandler::getInstance()

class NpcHandler
{
public:
	static NpcHandler &getInstance();

	void load();
	void unload();

	std::map<std::string, NpcPtr> &getNpcs();
	Npc &getNpc(std::string id);
	bool isInConversation();

private:
	NpcHandler();
	NpcHandler(NpcHandler&);
	void operator=(NpcHandler&);

	std::map<std::string, NpcPtr> mNpcMap;
};