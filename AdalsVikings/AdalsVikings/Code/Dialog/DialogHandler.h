#pragma once
#include "DialogueTree.h"
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <memory>

typedef std::unique_ptr<DialogueTree> DialogueTreePtr;

class DialogHandler
{
public:
	static void startDialogue(std::string id);
	static void reloadConversations();

	static void load(std::string levelFolder);
	static void unload();

	static DialogueTree &getDialogue(std::string id);
	static std::map<std::string, DialogueTreePtr> &getDialogues();

private:
	DialogHandler();
	DialogHandler(DialogHandler&);
	void operator=(DialogHandler&);
};
