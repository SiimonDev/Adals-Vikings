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

void DialogHandler::load(std::string levelFolder)
{
	instream.open(levelFolder);

	while (!instream.eof())
	{
		std::string id, filepath;
		instream >> id;
		instream >> filepath;

		if (id != "" || filepath != "")
		{

			DialogueTreePtr dialouge(new DialogueTree());
			dialouge->setDialogue(filepath);

			mDialogueMap.insert(std::make_pair(id, std::move(dialouge)));
			mDialogueMap[id]->load();
		}
	}

	instream.close();

}
void DialogHandler::unload(std::string levelFolder)
{
	instream.open(levelFolder);

	while (!instream.eof())
	{
		std::string id, filepath;
		instream >> id;
		instream >> filepath;

		if (id != "" || filepath != "")
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