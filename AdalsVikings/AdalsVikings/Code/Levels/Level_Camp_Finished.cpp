#include "Level_Camp_Finished.h"
#include <iostream>

Level_Camp_Finished::Level_Camp_Finished(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Camp_Finished;
}

void Level_Camp_Finished::update(sf::Time &frametime)
{
	changeLevel();
	Level::update(frametime);
}

void Level_Camp_Finished::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Camp_Finished::load()
{
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandler::getNpc("Brynja")));
	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandler::getNpc("Valdis")));

	mNpcs["Leifr"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Brynja"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));

	mNpcs["Valdis"]->setDialogue("Valdis_ClearingCamp");
	mNpcs["Brynja"]->setDialogue("Brynja_ClearingCamp");
	mNpcs["Leifr"]->setDialogue("Leifr_ClearingCamp");
	Level::load();
}

void Level_Camp_Finished::unload()
{
	Level::unload();
}

void Level_Camp_Finished::changeLevel()
{
}

void Level_Camp_Finished::checkInteractEvents()
{

}
void Level_Camp_Finished::checkEvents()
{

}