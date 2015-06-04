#include "BoatEvents.h"
#include <map>
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>

static std::map<BoatEvent::ID, bool> mHasBeenTriggerd;
static std::map<BoatEvent::ID, bool> mHasBeenHandled;

BoatEvents::BoatEvents()
{
}

void BoatEvents::initialize(std::string filePath)
{
	mHasBeenHandled.clear();
	mHasBeenTriggerd.clear();

	if (filePath == "")
	{
		for (int i = 0; i < BoatEvent::EVENT_SIZE; i++)
			mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));

		for (int i = 0; i < BoatEvent::EVENT_SIZE; i++)
			mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
	}
	else
	{
		std::ifstream itemFile(filePath);
		std::string line;
		for (int i = 0; i < BoatEvent::EVENT_SIZE; i++)
		{
			std::getline(itemFile, line);
			if (line == "0 0")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
				mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
			}
			else if (line == "1 0")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), true));
				mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
			}
			else if (line == "0 1")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
				mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), true));
			}
			else if (line == "1 1")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), true));
				mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), true));
			}
			else
			{
				std::cout << "Error Loading Event" << i << " in: " << filePath << std::endl;
				mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
				mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
			}
		}
		itemFile.close();
	}
}

void BoatEvents::triggerEvent(BoatEvent::ID event)
{
	mHasBeenTriggerd[event] = true;
}

void BoatEvents::handleEvent(BoatEvent::ID event)
{
	mHasBeenHandled[event] = true;
}
void BoatEvents::saveEvents(std::string filePath)
{
	std::ofstream itemFile(filePath);
	for (int i = 0; i < BoatEvent::EVENT_SIZE; i++)
	{
		if (!mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)] && !mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)])
			itemFile << "0 0" << std::endl;
		else if (mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)] && !mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)])
			itemFile << "1 0" << std::endl;
		else if (!mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)] && mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)])
			itemFile << "0 1" << std::endl;
		else if (mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)] && mHasBeenTriggerd[static_cast<BoatEvent::ID>(i)])
			itemFile << "1 1" << std::endl;
	}
	itemFile.close();
}

void BoatEvents::resetEvents()
{
	mHasBeenHandled.clear();
	mHasBeenTriggerd.clear();
}
bool BoatEvents::hasBeenHandled(BoatEvent::ID event)
{
	return mHasBeenHandled[event];
}

bool BoatEvents::hasBeenTriggered(BoatEvent::ID event)
{
	return mHasBeenTriggerd[event];
}