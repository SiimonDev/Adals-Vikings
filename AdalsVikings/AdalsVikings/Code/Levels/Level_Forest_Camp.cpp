#include "Level_Forest_Camp.h"
#include "..\Logics\AudioPlayer.h"
#include <iostream>

Level_Forest_Camp::Level_Forest_Camp(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mBackgroundID = LevelFolder::Forest_Camp;
}

void Level_Forest_Camp::restartSounds()
{
	AudioPlayer::playHDDSound(HDDSound::Forest_Camp_Ambient, true, 20);
	AudioPlayer::playHDDSound(HDDSound::Forest_Music, true, 20);
}

void Level_Forest_Camp::update(sf::Time &frametime)
{
	if (KeyboardState::isPressed(sf::Keyboard::Num1))
		mPlayer->addItemToInventory("bearDeer");
	mFireAnimation.animate(frametime);
	
	Level::update(frametime);
	changeLevel();
}

void Level_Forest_Camp::render(IndexRenderer &iRenderer)
{ 
	mFireAnimation.render(iRenderer);
	iRenderer.addSprite(mDruids, 50);
	Level::render(iRenderer);
}

void Level_Forest_Camp::load()
{
	RMI.loadResource(Footsteps::Dirt);
	mPortals[ForestCampToForestRoad] = &PortalLoader::getPortal(ForestCampToForestRoad);
	mPortals[ForestCampToForestRoad]->setWorking(true);

	RMI.loadResource(Texture::FireForestCampAnimation);
	RMI.loadResource(Texture::DruidsForest1);

	mNpcs["DruidLeader"] = NpcPtr(new Npc(NpcHandler::getNpc("DruidLeader")));
	mNpcs["Druids"] = NpcPtr(new Npc(NpcHandler::getNpc("Druids")));
	mNpcs["DruidLeader"]->setDialogue("Druids_ForestCamp1");
	mNpcs["Druids"]->setDialogue("Druids_ForestCamp1");

	if (Act1Events::hasBeenHandled(Act1Event::CampClearing_Leifr))
	{
		mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
		mNpcs["Leifr"]->setDialogue("Leifr_ForestCamp");
	}

	mFireAnimation.load(RMI.getResource(Texture::FireForestCampAnimation), sf::Vector2i(2, 4), sf::milliseconds(2000), sf::Time::Zero, true);
	mFireAnimation.setIndex(9999);
	mFireAnimation.setProportions(sf::Vector2f(961, 541));
	mFireAnimation.setScaleFromHeight(541 * 2);

	mDruids.setTexture(RMI.getResource(Texture::DruidsForest1));

	Level::load();

	mCurrentFootsteps = Footsteps::Dirt;
}

void Level_Forest_Camp::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	RMI.unloadResource(Texture::FireForestCampAnimation);
	Level::unload();
}

void Level_Forest_Camp::changeLevel()
{
	if (mPortals[ForestCampToForestRoad]->getActivated() && mPortals[ForestCampToForestRoad]->getWorking())
	{
		LVLMI.changeLevel(LevelFolder::Forest_Road);
		AudioPlayer::stopHDDSound(HDDSound::Forest_Camp_Ambient);
		mRestartSounds = true;
	}
}

void Level_Forest_Camp::checkInteractEvents()
{

}
void Level_Forest_Camp::checkEvents()
{
	if (DialogHandler::getDialogue("Druids_ForestCamp1").getIsOptionDisabled(3) &&
		DialogHandler::getDialogue("Druids_ForestCamp1").getIsOptionDisabled(5) &&
		!Act1Events::hasBeenTriggered(Act1Event::ForestCamp_NeedFireQuest))
		Act1Events::triggerEvent(Act1Event::ForestCamp_NeedFireQuest);
}