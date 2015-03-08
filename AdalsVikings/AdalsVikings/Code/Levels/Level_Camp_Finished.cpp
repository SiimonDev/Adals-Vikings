#include "Level_Camp_Finished.h"
#include <iostream>

Level_Camp_Finished::Level_Camp_Finished(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
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
	RMI.loadResource(Footsteps::Dirt);
	mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
	mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brynja")));
	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));

	mNpcs["Leifr"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Brynja"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));

	mNpcs["Valdis"]->setDialogue("Valdis_ClearingCamp");
	mNpcs["Brynja"]->setDialogue("Brynja_ClearingCamp");
	mNpcs["Leifr"]->setDialogue("Leifr_ClearingCamp");
	Level::load();

	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Camp_Finished::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
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