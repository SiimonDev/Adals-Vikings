#include "BoatEvents.h"
#include <map>

static std::map<BoatEvent::ID, bool> mHasBeenTriggerd;
static std::map<BoatEvent::ID, bool> mHasBeenHandled;

BoatEvents::BoatEvents()
{
}

void BoatEvents::initialize()
{
	mHasBeenHandled.clear();
	mHasBeenTriggerd.clear();

	for (int i = 0; i < BoatEvent::EVENT_SIZE; i++)
		mHasBeenTriggerd.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));

	for (int i = 0; i < BoatEvent::EVENT_SIZE; i++)
		mHasBeenHandled.insert(std::make_pair(static_cast<BoatEvent::ID>(i), false));
}

void BoatEvents::triggerEvent(BoatEvent::ID event)
{
	mHasBeenTriggerd[event] = true;
}

void BoatEvents::handleEvent(BoatEvent::ID event)
{
	mHasBeenHandled[event] = true;
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