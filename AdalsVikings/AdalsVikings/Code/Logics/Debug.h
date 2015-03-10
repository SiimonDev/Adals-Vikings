#pragma once
#include <SFML/Graphics.hpp>
#include "..\Objects\Player.h"

#define DebugI Debug::getInstance()
#define DebugMode Debug::getInstance().debugMode()

class Debug
{
public:
	static Debug &getInstance();

	void initialize(Player &player);
	void update(sf::Time frameTime);
	bool debugMode();

private:
	Player* mPlayer;

	bool mDebugMode;

	Debug();
	Debug(Debug&);
	void operator=(Debug&);
};