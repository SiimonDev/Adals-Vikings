#pragma once
#include "Dialog.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Objects\Player.h"
#include <string>

#define PlayerMonologueI PlayerMonologue::getInstance()

class PlayerMonologue
{
public:
	static PlayerMonologue &getInstance();

	void setPosition(sf::Vector2f pos);
	void setText(std::string text);
	void setOutlineColor(sf::Color &color);
	void setDisplay(bool value);

	void load();
	void unload();

	void displayDialog(Dialog &dialog);
	void update(sf::Time &time);
	void render(IndexRenderer &iRenderer);

	bool &getDisplay();
private:
	sf::Time mTimePassed;
	sf::Text mText;
	sf::Vector2f mPosition;
	sf::RoundedRectangleShape mTextRect;

	Dialog mCurrentDialog;

	bool mDisplay;

	PlayerMonologue();
	PlayerMonologue(const PlayerMonologue&);
	void operator=(const PlayerMonologue&);
};