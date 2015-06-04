#include "Act1Events.h"
#include <map>
#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>

static std::map<Act1Event::ID, bool> mHasBeenTriggerd;
static std::map<Act1Event::ID, bool> mHasBeenHandled;

Act1Events::Act1Events()
{
}

void Act1Events::initialize(std::string filePath)
{
	mHasBeenHandled.clear();
	mHasBeenTriggerd.clear();

	if (filePath == "")
	{
		for (int i = 0; i < Act1Event::EVENT_SIZE; i++)
			mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));

		for (int i = 0; i < Act1Event::EVENT_SIZE; i++)
			mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
	}
	else
	{
		std::ifstream itemFile(filePath);
		std::string line;
		for (int i = 0; i < Act1Event::EVENT_SIZE; i++)
		{
			std::getline(itemFile, line);
			if (line == "0 0")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
				mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
			}
			else if (line == "1 0")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), true));
				mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
			}
			else if (line == "0 1")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
				mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), true));
			}
			else if (line == "1 1")
			{
				mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), true));
				mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), true));
			}
			else
			{
				std::cout << "Error Loading Event" << i << " in: " << filePath << std::endl;
				mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
				mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
			}
		}
		itemFile.close();
	}
}

void Act1Events::triggerEvent(Act1Event::ID event)
{
	mHasBeenTriggerd[event] = true;
}

void Act1Events::handleEvent(Act1Event::ID event)
{
	mHasBeenHandled[event] = true;
}
void Act1Events::saveEvents(std::string filePath)
{
	std::ofstream itemFile(filePath);
	std::string line;
	for (int i = 0; i < Act1Event::EVENT_SIZE; i++)
	{
		if (!mHasBeenTriggerd[static_cast<Act1Event::ID>(i)] && !mHasBeenTriggerd[static_cast<Act1Event::ID>(i)])
			itemFile << "0 0" << std::endl;
		else if (mHasBeenTriggerd[static_cast<Act1Event::ID>(i)] && !mHasBeenTriggerd[static_cast<Act1Event::ID>(i)])
			itemFile << "1 0" << std::endl;
		else if (!mHasBeenTriggerd[static_cast<Act1Event::ID>(i)] && mHasBeenTriggerd[static_cast<Act1Event::ID>(i)])
			itemFile << "0 1" << std::endl;
		else if (mHasBeenTriggerd[static_cast<Act1Event::ID>(i)] && mHasBeenTriggerd[static_cast<Act1Event::ID>(i)])
			itemFile << "1 1" << std::endl;
	}
	itemFile.close();
}
void Act1Events::resetEvents()
{
	mHasBeenHandled.clear();
	mHasBeenTriggerd.clear();
}
bool Act1Events::hasBeenHandled(Act1Event::ID event)
{
	return mHasBeenHandled[event];
}

bool Act1Events::hasBeenTriggered(Act1Event::ID event)
{
	return mHasBeenTriggerd[event];
}
