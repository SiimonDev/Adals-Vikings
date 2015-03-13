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
				Act1Events::handleEvent(Act1Event::CampFinished_Conversation);
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

	RMI.loadResource(Texture::FireCampAnimation);

	mPlayer->setPosition(sf::Vector2f(985, 740));
	mPlayer->UpdateAnimationStyle();

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

	mNpcs["Leifr"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Brynja"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Yngvarr"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Dagny"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Alfr"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Finnr"]->setscale(sf::Vector2f(0.42, 0.42));
	mNpcs["Brandr"]->setscale(sf::Vector2f(0.4, 0.4));

	mNpcs["Leifr"]->setPosition(sf::Vector2f(800, 880));
	mNpcs["Brynja"]->setPosition(sf::Vector2f(890,760));
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

	mNpcs["Valdis"]->setDialogue("Valdis_ClearingCamp");
	mNpcs["Brynja"]->setDialogue("Brynja_ClearingCamp");
	mNpcs["Leifr"]->setDialogue("Leifr_ClearingCamp");
	Level::load();

	mCurrentFootsteps = Footsteps::Dirt;
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