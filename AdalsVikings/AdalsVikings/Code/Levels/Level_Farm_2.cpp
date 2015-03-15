#include "Level_Farm_2.h"
#include <iostream>

Level_Farm_2::Level_Farm_2(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Farm_2;
}

void Level_Farm_2::restartSounds()
{

}

void Level_Farm_2::update(sf::Time &frametime)
{
	Level::update(frametime);
	changeLevel();
}

void Level_Farm_2::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
}

void Level_Farm_2::load()
{
	mPortals[Farm2ToFarm1] = &PortalLoader::getPortal(Farm2ToFarm1);
	mPortals[Farm2ToFarm1]->setWorking(true);

	mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));
	mNpcs["Valdis"]->setDialogue("Valdis_Farm");

	Level::load();
}

void Level_Farm_2::unload()
{
	Level::unload();
}

void Level_Farm_2::changeLevel()
{
	if (mPortals[Farm2ToFarm1]->getActivated() && mPortals[Farm2ToFarm1]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Farm_1);
	}
}

void Level_Farm_2::checkInteractEvents()
{

}
void Level_Farm_2::checkEvents()
{

}
