#pragma once
#include "NPC.h"
#include <map>
#include <memory>

typedef std::unique_ptr<Npc> NpcPtr;

class NpcHandler
{
public:
	static void load();
	static void unload();

	static std::map<std::string, NpcPtr> &getNpcs();
	static Npc &getNpc(std::string id);
	static bool isInConversation();

private:
	NpcHandler();
	NpcHandler(NpcHandler&);
	void operator=(NpcHandler&);
};