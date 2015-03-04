#include "Act1Events.h"
#include <map>


static std::map<Act1Event::ID, bool> mHasBeenTriggerd;
static std::map<Act1Event::ID, bool> mHasBeenHandled;

Act1Events::Act1Events()
{
}

void Act1Events::initialize()
{
	mHasBeenHandled.clear();
	mHasBeenTriggerd.clear();

	for (int i = 0; i < Act1Event::EVENT_SIZE; i++)
		mHasBeenTriggerd.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));

	for (int i = 0; i < Act1Event::EVENT_SIZE; i++)
		mHasBeenHandled.insert(std::make_pair(static_cast<Act1Event::ID>(i), false));
}

void Act1Events::triggerEvent(Act1Event::ID event)
{
	mHasBeenTriggerd[event] = true;
}

void Act1Events::handleEvent(Act1Event::ID event)
{
	mHasBeenHandled[event] = true;
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
