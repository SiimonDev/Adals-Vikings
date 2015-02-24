#pragma once
namespace Act1Event
{
	enum ID
	{
		Beach_Intro,
		Beach_Alfr,
		Beach_Dagny,
		Beach_Finnr,
		Beach_Leifr,
		Beach_Yngvarr,
		Beach_Valdis,
		Beach_Ending,
		EVENT_SIZE
	};
}

class Act1Events
{
public:
	static void initialize();
	static void triggerEvent(Act1Event::ID event);
	static void handleEvent(Act1Event::ID event);
	static void resetEvents();

	static bool hasBeenHandled(Act1Event::ID event);
	static bool hasBeenTriggered(Act1Event::ID event);

private:
	Act1Events();
	Act1Events(const Act1Events&);
	void operator=(const Act1Events&);
};

