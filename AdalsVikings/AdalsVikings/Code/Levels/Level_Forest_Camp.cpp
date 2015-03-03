#include "Level_Forest_Camp.h"
#include <iostream>

Level_Forest_Camp::Level_Forest_Camp(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Camp;
}

void Level_Forest_Camp::update(sf::Time &frametime)
{
	mFireAnimation.animate(frametime);

	changeLevel();
	Level::update(frametime);
}

void Level_Forest_Camp::render(IndexRenderer &iRenderer)
{ 
	mFireAnimation.render(iRenderer);
	iRenderer.addSprite(mDruids, 50);
	Level::render(iRenderer);
}

void Level_Forest_Camp::load()
{
	mPortals[ForestCampToForestRoad] = &PortalLoader::getPortal(ForestCampToForestRoad);
	mPortals[ForestCampToForestRoad]->setWorking(true);

	RMI.loadResource(Texture::FireForestCampAnimation);
	RMI.loadResource(Texture::DruidsForest1);

	mNpcs["DruidLeader"] = NpcPtr(new Npc(NpcHandler::getNpc("DruidLeader")));
	mNpcs["Druids"] = NpcPtr(new Npc(NpcHandler::getNpc("Druids")));
	mNpcs["DruidLeader"]->setDialogue("Druids_ForestCamp1");
	mNpcs["Druids"]->setDialogue("Druids_ForestCamp1");

	mFireAnimation.load(RMI.getResource(Texture::FireForestCampAnimation), sf::Vector2i(2, 4), sf::milliseconds(2000), sf::Time::Zero, true);
	mFireAnimation.setIndex(9999);
	mFireAnimation.setProportions(sf::Vector2f(961, 541));
	mFireAnimation.setScaleFromHeight(541 * 2);

	mDruids.setTexture(RMI.getResource(Texture::DruidsForest1));

	Level::load();
}

void Level_Forest_Camp::unload()
{
	RMI.unloadResource(Texture::FireForestCampAnimation);
	Level::unload();
}

void Level_Forest_Camp::changeLevel()
{
	if (mPortals[ForestCampToForestRoad]->getActivated() && mPortals[ForestCampToForestRoad]->getWorking())
		LVLMI.changeLevel(LevelFolder::Forest_Road);
}

void Level_Forest_Camp::checkInteractEvents()
{

}
void Level_Forest_Camp::checkEvents()
{

}

//void Level_Forest_Camp::setNearbyLevels()
//{
//	for (std::map<LevelFolder::ID, LevelPtr>::iterator it = LVLMI.getCurrentLevels().begin(); it != LVLMI.getCurrentLevels().end(); ++it)
//	{
//		if (it->first == LevelFolder::Forest_Road)
//			it->second->setIsNearbyLevel(true);
//		else
//			it->second->setIsNearbyLevel(false);
//	}
//}
