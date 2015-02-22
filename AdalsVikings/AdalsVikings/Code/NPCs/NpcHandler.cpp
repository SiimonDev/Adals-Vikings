#include "NpcHandler.h"
#include "..\Logics\PathFinder.h"

#define CreateNpc mNpcMap.insert(std::make_pair

static std::map<std::string, NpcPtr> mNpcMap;

NpcHandler::NpcHandler()
{
}

void NpcHandler::initialize()
{
	NpcPtr Valdis(new Npc());
	NpcPtr Leifr(new Npc());
	NpcPtr Finnr(new Npc());
	NpcPtr Brynja(new Npc());
	NpcPtr Alfr(new Npc());
	NpcPtr Dagny(new Npc());
	NpcPtr Brandr(new Npc());
	NpcPtr Yngvarr(new Npc());

	Valdis->setName("Valdis");
	Valdis->setIdleAnimation(Textures::ValdisIdle, "assets/images/Valdis/character_valdis_blink.png", sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(7));
	Valdis->SetTalkAnimation(Textures::ValdisTalk, "assets/images/Valdis/character_valdis_talk.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
	Valdis->setPosition(sf::Vector2f(1250, 620));
	Valdis->setInteractionPosition(sf::Vector2f(1200, 720));
	Valdis->setDialogue("Valdis");
	Valdis->setColor(sf::Color(50, 205, 50));
	Valdis->setIndex(14);
	Valdis->setProportions(sf::Vector2f(167.5, 436));
	Valdis->setscale(sf::Vector2f(0.45f, 0.45f));
	Valdis->setRightWay(false);

	Leifr->setName("Leifr");
	Leifr->setIdleAnimation(Textures::LeifrIdle, "assets/images/leifr/character_leifr_sit_blink.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	Leifr->SetTalkAnimation(Textures::LeifrTalk, "assets/images/leifr/character_leifr_sit_talk.png", sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Leifr->setPosition(sf::Vector2f(460, 620));
	Leifr->setInteractionPosition(sf::Vector2f(600, 630));
	Leifr->setColor(sf::Color(72, 209, 204));
	Leifr->setDialogue("Leifr");
	Leifr->setIndex(14);
	Leifr->setProportions(sf::Vector2f(286, 427));
	Leifr->setscale(sf::Vector2f(0.5f, 0.5f));
	Leifr->setRightWay(false);

	Finnr->setName("Finnr");
	Finnr->setIdleAnimation(Textures::FinnrIdle, "assets/images/finnr/character_finnr_blink.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(8));
	Finnr->SetTalkAnimation(Textures::FinnrTalk, "assets/images/finnr/character_finnr_talk.png", sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Finnr->setPosition(sf::Vector2f(580, 620));
	Finnr->setInteractionPosition(sf::Vector2f(600, 630));
	Finnr->setColor(sf::Color(173, 216, 230));
	Finnr->setDialogue("Finnr");
	Finnr->setIndex(14);
	Finnr->setProportions(sf::Vector2f(286, 427));
	Finnr->setscale(sf::Vector2f(0.5f, 0.5f));
	Finnr->setRightWay(false);

	Brynja->setName("Brynja");
	Brynja->setIdleAnimation(Textures::BrynjaIdle, "assets/images/Brynja/character_brynja_blink.png", sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(5));
	Brynja->SetTalkAnimation(Textures::BrynjaTalk, "assets/images/Brynja/character_brynja_talk.png", sf::Vector2i(4, 1), sf::milliseconds(600), sf::Time::Zero);
	Brynja->setColor(sf::Color(178, 34, 34));
	Brynja->setDialogue("Brynja");
	Brynja->setIndex(14);
	Brynja->setProportions(sf::Vector2f(290, 452));
	Brynja->setPosition(sf::Vector2f(1080, 620));
	Brynja->setInteractionPosition(sf::Vector2f(1050, 620));
	Brynja->setscale(sf::Vector2f(0.75f, 0.75f));
	Brynja->setRightWay(false);

	Alfr->setName("Alfr");
	Alfr->setIdleAnimation(Textures::AlfrIdle, "assets/images/Alfr/character_alfr.png", sf::Vector2i(1, 1), sf::milliseconds(10000), sf::seconds(9999));
	Alfr->SetTalkAnimation(Textures::AlfrTalk, "assets/images/Alfr/character_alfr_talk.png", sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Alfr->setPosition(sf::Vector2f(320, 790));
	Alfr->setInteractionPosition(sf::Vector2f(350, 790));
	Alfr->setColor(sf::Color(210, 105, 30));
	Alfr->setDialogue("Alfr");
	Alfr->setIndex(15);
	Alfr->setProportions(sf::Vector2f(204, 452));
	Alfr->setscale(sf::Vector2f(0.5f, 0.5f));
	Alfr->setRightWay(false);

	Dagny->setName("Dagny");
	Dagny->setIdleAnimation(Textures::DagnyIdle, "assets/images/Dagny/character_dagny_blink.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(4));
	Dagny->SetTalkAnimation(Textures::DagnyTalk, "assets/images/Dagny/character_dagny_talk.png", sf::Vector2i(4, 1), sf::milliseconds(350), sf::Time::Zero);
	Dagny->setPosition(sf::Vector2f(1565, 590));
	Dagny->setInteractionPosition(sf::Vector2f(1580, 590));
	Dagny->setColor(sf::Color(139, 0, 139));
	Dagny->setDialogue("Dagny");
	Dagny->setIndex(15);
	Dagny->setProportions(sf::Vector2f(126, 322));
	Dagny->setscale(sf::Vector2f(0.7f, 0.7f));
	Dagny->setRightWay(false);

	Brandr->setName("Brandr");
	Brandr->setIdleAnimation(Textures::BrandrIdle, "assets/images/Brandr/character_brandr_blink.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(3.7));
	Brandr->SetTalkAnimation(Textures::BrandrTalk, "assets/images/Brandr/character_brandr_talk.png", sf::Vector2i(6, 1), sf::milliseconds(750), sf::Time::Zero);
	Brandr->setPosition(sf::Vector2f(800, 650));
	Brandr->setInteractionPosition(sf::Vector2f(870, 830));
	Brandr->setColor(sf::Color(255, 215, 0));
	Brandr->setDialogue("Brandr");
	Brandr->setIndex(15);
	Brandr->setProportions(sf::Vector2f(181, 525));
	Brandr->setscale(sf::Vector2f(0.45f, 0.45f));
	Brandr->setRightWay(true);

	Yngvarr->setName("Yngvarr");
	Yngvarr->setIdleAnimation(Textures::YngvarrIdle, "assets/images/Yngvarr/character_yngvarr_blink.png", sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5.2));
	Yngvarr->SetTalkAnimation(Textures::YngvarrTalk, "assets/images/Yngvarr/character_yngvarr_talk.png", sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
	Yngvarr->setPosition(sf::Vector2f(900, 650));
	Yngvarr->setInteractionPosition(sf::Vector2f(1000, 780));
	Yngvarr->setColor(sf::Color(176, 196, 222));
	Yngvarr->setDialogue("Yngvarr");
	Yngvarr->setIndex(15);
	Yngvarr->setProportions(sf::Vector2f(148, 472));
	Yngvarr->setscale(sf::Vector2f(0.55f, 0.55f));
	Yngvarr->setRightWay(false);

	CreateNpc("Valdis", std::move(Valdis)));
	CreateNpc("Leifr", std::move(Leifr)));
	CreateNpc("Finnr", std::move(Finnr)));
	CreateNpc("Brynja", std::move(Brynja)));
	CreateNpc("Alfr", std::move(Alfr)));
	CreateNpc("Dagny", std::move(Dagny)));
	CreateNpc("Brandr", std::move(Brandr)));
	CreateNpc("Yngvarr", std::move(Yngvarr)));
}

void NpcHandler::unload()
{
	// Unload NPCs
	for (std::map<std::string, NpcPtr>::const_iterator it = mNpcMap.begin(); it != mNpcMap.end(); it++)
		it->second->unload();
	mNpcMap.clear();
}

std::map<std::string, NpcPtr> &NpcHandler::getNpcs()
{
	return mNpcMap;
}

Npc &NpcHandler::getNpc(std::string id)
{
	auto found = mNpcMap.find(id);
	return *found->second;
}

bool NpcHandler::isInConversation()
{
	for (std::map<std::string, NpcPtr>::const_iterator it = mNpcMap.begin(); it != mNpcMap.end(); it++)
		return (it->second->getActiveConversation());
	return false;
}
