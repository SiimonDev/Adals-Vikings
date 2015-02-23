#include "Beach_Level.h"
#include "..\Logics\ResourceManager.h"
#include "..\Logics\AudioPlayer.h"
#include "..\Interface\LoadingScreen.h"
#include "..\Logics\KeyboardState.h"
#include <iostream>

Beach_level::Beach_level(Player &player, ActionWheel &actionWheel)
	: Level(player, actionWheel)
{
	mFolderPath = "Assets/MapFiles/Beach/";
}

void Beach_level::update(sf::Time &frametime)
{
	if (KeyboardState::isPressed(sf::Keyboard::J))
		LSI.startLoading(LoadTest);
	mWaveAnimation.animate(frametime);
	Level::update(frametime);
	changeLevel();
}

void Beach_level::render(IndexRenderer &iRenderer)
{
	mWaveAnimation.render(iRenderer);
	Level::render(iRenderer);
}

void Beach_level::load()
{

	mPortals[Portal3] = LPortalPtr(new Portal(PortalLoader::getPortal(Portal3)));
	/* ==== Load Npcs and set right position, dialogue, scale and so on... ===== */
	mNpcs["Yngvarr"] = LNpcPtr(new Npc(NpcHandler::getNpc("Yngvarr")));
	mNpcs["Dagny"] = LNpcPtr(new Npc(NpcHandler::getNpc("Dagny")));
	mNpcs["Alfr"] = LNpcPtr(new Npc(NpcHandler::getNpc("Alfr")));
	mNpcs["Leifr"] = LNpcPtr(new Npc(NpcHandler::getNpc("Leifr")));
	mNpcs["Finnr"] = LNpcPtr(new Npc(NpcHandler::getNpc("Finnr")));
	mNpcs["Valdis"] = LNpcPtr(new Npc(NpcHandler::getNpc("Valdis")));

	/* ==== Yngvarr ===== */
	mNpcs["Yngvarr"]->setRightWay(false);
	mNpcs["Yngvarr"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Yngvarr"]->setPosition(sf::Vector2f(350, 680));
	mNpcs["Yngvarr"]->setInteractionPosition(sf::Vector2f(400, 770));
	mNpcs["Yngvarr"]->setDialogue("Yngvarr");
	mNpcs["Yngvarr"]->setIndex(5);

	/* ==== Yngvarr ===== */
	mNpcs["Dagny"]->setRightWay(true);
	mNpcs["Dagny"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Dagny"]->setPosition(sf::Vector2f(250, 700));
	mNpcs["Dagny"]->setInteractionPosition(sf::Vector2f(400, 770));
	mNpcs["Dagny"]->setDialogue("Dagny");
	mNpcs["Dagny"]->setIndex(5);

	/* ==== Alfr ===== */
	mNpcs["Alfr"]->setRightWay(false);
	mNpcs["Alfr"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Alfr"]->setPosition(sf::Vector2f(1250, 500));
	mNpcs["Alfr"]->setInteractionPosition(sf::Vector2f(1200, 570));
	mNpcs["Alfr"]->setDialogue("Alfr");
	mNpcs["Alfr"]->setIndex(5);

	/* ==== Leifr ===== */
	RMI.unload(Textures::LeifrIdle);
	RMI.unload(Textures::LeifrTalk);
	RMI.load(Textures::LeifrIdle, "assets/images/Leifr/character_leifr_blink.png");
	RMI.load(Textures::LeifrTalk, "assets/images/Leifr/character_leifr_talk.png");
	mNpcs["Leifr"]->setIdleAnimation(Textures::LeifrIdle, "assets/images/Leifr/character_leifr_blink.png", sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(7.2));
	mNpcs["Leifr"]->SetTalkAnimation(Textures::LeifrTalk, "assets/images/Leifr/character_leifr_talk.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
	mNpcs["Leifr"]->setRightWay(true);
	mNpcs["Leifr"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Leifr"]->setPosition(sf::Vector2f(700, 500));
	mNpcs["Leifr"]->setInteractionPosition(sf::Vector2f(750, 570));
	mNpcs["Leifr"]->setDialogue("Leifr");
	mNpcs["Leifr"]->setIndex(5);

	/* ==== Finnr ===== */
	mNpcs["Finnr"]->setRightWay(false);
	mNpcs["Finnr"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Finnr"]->setPosition(sf::Vector2f(1600, 450));
	mNpcs["Finnr"]->setInteractionPosition(sf::Vector2f(1550, 530));
	mNpcs["Finnr"]->setDialogue("Finnr");
	mNpcs["Finnr"]->setIndex(5);

	/* ==== Valdis ===== */
	mNpcs["Valdis"]->setRightWay(true);
	mNpcs["Valdis"]->setscale(sf::Vector2f(0.4, 0.4));
	mNpcs["Valdis"]->setPosition(sf::Vector2f(400, 1000));
	mNpcs["Valdis"]->setInteractionPosition(sf::Vector2f(450, 1070));
	mNpcs["Valdis"]->setDialogue("Valdis");
	mNpcs["Valdis"]->setIndex(5);

	/* ================================================================ */

	RMI.load(Textures::Wave, "Assets/MapFiles/Beach/waves.png");
	mWaveAnimation.load(RMI.getTexture(Textures::Wave), sf::Vector2i(10, 9), sf::seconds(7), sf::seconds(5), true);
	mWaveAnimation.setIndex(4);
	mWaveAnimation.setProportions(sf::Vector2f(1170, 640));
	mWaveAnimation.getSprite().setOrigin(mWaveAnimation.getSprite().getTextureRect().width, mWaveAnimation.getSprite().getTextureRect().height);
	mWaveAnimation.setPadding(1);
	mWaveAnimation.setPosition(sf::Vector2f(1920 + 3, 1080 + 3));
	Level::load();

	mTileMap.addCollision(mNpcs["Valdis"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Leifr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Finnr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Dagny"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Alfr"]->getCollisionRect());
	mTileMap.addCollision(mNpcs["Yngvarr"]->getCollisionRect());
}

void Beach_level::unload()
{
	RMI.unload(Textures::Wave);
	Level::unload();
}
void Beach_level::changeLevel()
{
	if (mPortals[Portal3]->getActivated())
	{
		LSI.startLoading(LoadTest);
	}
}
void Beach_level::checkInteractEvents()
{

}