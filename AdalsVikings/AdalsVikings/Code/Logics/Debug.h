#pragma once
#include <SFML/Graphics.hpp>

#define DebugI Debug::getInstance()
#define DebugMode Debug::getInstance().debugMode()

class Debug
{
public:
	static Debug &getInstance();
	void update(sf::Time frameTime);
	bool debugMode();

private:
	bool mDebugMode;

	Debug();
	Debug(Debug&);
	void operator=(Debug&);
};