#include "Level_Camp_Finished.h"
#include <iostream>

Level_Camp_Finished::Level_Camp_Finished(Player &player, HUD &hud, ActionWheel &actionWheel)
	: Level(player, hud, actionWheel)
{
	mBackgroundID = LevelFolder::Camp_Finished;
}

void Level_Camp_Finished::update(sf::Time &frametime)
{
	mCampFire.animate(frametime);
	if (Act1Events::hasBeenTriggered(Act1Event::CampFinished_Conversation) && !Act1Events::hasBeenHandled(Act1Event::CampFinished_Conversation))
	{
		if (!mFade1)
		{
			if (!mHasSpawned)
			{
				mPlayer->setPosition(sf::Vector2f(985, 740));
				mPlayer->UpdateAnimationStyle();

				mHasSpawned = true;
			}
			FadeI.fadeIn(frametime);
			if (FadeI.getFaded())
			{
				DialogHandler::getDialogue("All_FinishedCamp").startDialogue();
				mFade1 = true;
			}
		}

		if (!mFade2 && DialogHandler::getDialogue("All_FinishedCamp").getHasStopped())
		{
			FadeI.fadeOut(frametime);
			if (FadeI.getFaded())
			{
				mFade2 = true;
				mNpcs.clear();
				Act1Events::handleEvent(Act1Event::CampFinished_Conversation);
				LVLMI.changeLevel(LevelFolder::Road);
			}
		}
	}

	changeLevel();
	Level::update(frametime);
}

void Level_Camp_Finished::render(IndexRenderer &iRenderer)
{
	Level::render(iRenderer);
	mCampFire.render(iRenderer);
}

void Level_Camp_Finished::load()
{
	RMI.loadResource(Footsteps::Dirt);
	if (mPlayer->hasItemInInventory("torch"))
	{
		mPortals[CampFinishedToRoad] = &PortalLoader::getPortal(CampFinishedToRoad);
		mPortals[CampFinishedToRoad]->setCannotDialogue("Hello!");

		RMI.loadResource(Texture::FireCampAnimation);

		mCampFire.load(RMI.getResource(Texture::FireCampAnimation), sf::Vector2i(3, 1), sf::milliseconds(300), sf::Time::Zero, true);
		mCampFire.setIndex(5);
		mCampFire.setProportions(sf::Vector2f(99, 115));
		mCampFire.setScaleFromHeight(115);
		mCampFire.setPosition(sf::Vector2f(900, 720));

		mNpcs["Leifr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Leifr")));
		mNpcs["Brynja"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brynja")));
		mNpcs["Valdis"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Valdis")));
		mNpcs["Yngvarr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Yngvarr")));
		mNpcs["Dagny"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Dagny")));
		mNpcs["Alfr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Alfr")));
		mNpcs["Finnr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Finnr")));
		mNpcs["Brandr"] = NpcPtr(new Npc(NpcHandlerI.getNpc("Brandr")));

		mNpcs["Leifr"]->setScale(sf::Vector2f(0.32, 0.32));
		mNpcs["Brynja"]->setScale(sf::Vector2f(0.42, 0.42));
		mNpcs["Valdis"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Yngvarr"]->setScale(sf::Vector2f(0.42, 0.42));
		mNpcs["Dagny"]->setScale(sf::Vector2f(0.42, 0.42));
		mNpcs["Alfr"]->setScale(sf::Vector2f(0.4, 0.4));
		mNpcs["Finnr"]->setScale(sf::Vector2f(0.42, 0.42));
		mNpcs["Brandr"]->setScale(sf::Vector2f(0.4, 0.4));

		mNpcs["Leifr"]->setPosition(sf::Vector2f(800, 880));
		mNpcs["Brynja"]->setPosition(sf::Vector2f(890, 760));
		mNpcs["Valdis"]->setPosition(sf::Vector2f(1110, 790));
		mNpcs["Yngvarr"]->setPosition(sf::Vector2f(1050, 780));
		mNpcs["Dagny"]->setPosition(sf::Vector2f(980, 880));
		mNpcs["Alfr"]->setPosition(sf::Vector2f(890, 880));
		mNpcs["Finnr"]->setPosition(sf::Vector2f(1050, 850));
		//mNpcs["Brandr"]->setPosition(sf::Vector2f());

		mNpcs["Leifr"]->setFlip(true);
		mNpcs["Brynja"]->setFlip(true);
		mNpcs["Valdis"]->setFlip(false);
		mNpcs["Yngvarr"]->setFlip(false);
		mNpcs["Dagny"]->setFlip(false);
		mNpcs["Alfr"]->setFlip(true);
		mNpcs["Finnr"]->setFlip(false);

		mNpcs["Leifr"]->setIndex(10);
		mNpcs["Brynja"]->setIndex(5);
		mNpcs["Valdis"]->setIndex(5);
		mNpcs["Yngvarr"]->setIndex(5);
		mNpcs["Dagny"]->setIndex(10);
		mNpcs["Alfr"]->setIndex(10);
		mNpcs["Finnr"]->setIndex(10);
		mNpcs["Brandr"]->setIndex(5);
		mCurrentFootsteps = Footsteps::Dirt;
	}
	Level::load();

}

void Level_Camp_Finished::unload()
{
	RMI.unloadResource(Footsteps::Dirt);
	RMI.unloadResource(Texture::FireCampAnimation);
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
	if (Act1Events::hasBeenHandled(Act1Event::LightCampFire) && !Act1Events::hasBeenTriggered(Act1Event::CampFinished_Conversation))
		Act1Events::triggerEvent(Act1Event::CampFinished_Conversation);
}