#pragma once
#include "DialogueTree.h"
#include "..\Objects\Player.h"
#include <string>
#include <map>
#include <memory>

typedef std::unique_ptr<DialogueTree> DialogueTreePtr;

class DialogHandler
{
public:
	static void startDialogue(std::string id);
	static void reloadConversations();

	static void load(bool reset, Player &player);
	static void unload();

	static DialogueTree &getDialogue(std::string id);
	static std::map<std::string, DialogueTreePtr> &getDialogues();

private:
	DialogHandler();
	DialogHandler(DialogHandler&);
	void operator=(DialogHandler&);
};

