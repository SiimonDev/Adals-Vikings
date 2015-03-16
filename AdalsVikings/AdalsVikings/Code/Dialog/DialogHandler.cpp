#include "DialogHandler.h"
#include <fstream>

static std::ifstream instream;
static std::map<std::string, DialogueTreePtr> mDialogueMap;

DialogHandler::DialogHandler()
{
}

void DialogHandler::startDialogue(std::string id)
{
	for (std::map<std::string, DialogueTreePtr>::const_iterator it = mDialogueMap.begin(); it != mDialogueMap.end(); it++)
	{
		if (it->second->getActiveConversation())
			it->second->stopConversation();
	}
	mDialogueMap.find(id)->second->startDialogue();
}
void DialogHandler::reloadConversations()
{
	for (std::map<std::string, DialogueTreePtr>::const_iterator it = mDialogueMap.begin(); it != mDialogueMap.end(); it++)
		it->second->reloadConverstaion();
}

void DialogHandler::load(bool reset)
{
	RMI.loadResource(Font::Skranji_regular);
	instream.open("assets/textfiles/Dialogues.txt");

	while (!instream.eof())
	{
		std::string id, filepath;
		instream >> id;
		instream >> filepath;

		if (id != "" && id.find("---") == std::string::npos && filepath != "" && filepath.find("---") == std::string::npos)
		{

			DialogueTreePtr dialouge(new DialogueTree(Font::Skranji_regular));
			dialouge->setDialogue(filepath);

			mDialogueMap.insert(std::make_pair(id, std::move(dialouge)));
			mDialogueMap[id]->load(reset);
		}
	}

	instream.close();

}
void DialogHandler::unload()
{
	RMI.unloadResource(Font::Skranji_regular);
	instream.open("assets/textfiles/Dialogues.txt");

	while (!instream.eof())
	{
		std::string id, filepath;
		instream >> id;
		instream >> filepath;

		if (id != "" || id.find("---") == std::string::npos || filepath != "" || filepath.find("---") == std::string::npos)
		{
			mDialogueMap.erase(id);
		}
	}

	instream.close();
}

DialogueTree &DialogHandler::getDialogue(std::string id)
{
	return *mDialogueMap.find(id)->second;
}
std::map<std::string, DialogueTreePtr> &DialogHandler::getDialogues()
{
	return mDialogueMap;
}