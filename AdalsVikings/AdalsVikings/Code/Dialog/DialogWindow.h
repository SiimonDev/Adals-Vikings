#pragma once
#include "Dialog.h"
#include "..\Logics\IndexRenderer.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\IndexRenderer.h"
#include <string>

class DialogWindow
{
public:
	static void setPosition(sf::Vector2f &pos);
	static void setFont(Font::ID id);
	static void setText(std::string text);

	static void setOutlineColor(sf::Color &color);

	static void load();
	static void unload();

	static void displayDialog(Dialog &dialog);
	static void update(sf::Time &time);
	static void render(IndexRenderer &iRenderer);

private:
	DialogWindow();
	DialogWindow(const DialogWindow&);
	void operator=(const DialogWindow&);
};