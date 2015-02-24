#include "NpcHandler.h"
#include "..\Logics\PathFinder.h"

#define CreateNpc mNpcMap.insert(std::make_pair

static std::map<std::string, NpcPtr> mNpcMap;

NpcHandler::NpcHandler()
{
}

void NpcHandler::load()
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
	Valdis->setIdleAnimation(Textures::ValdisIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(7));
	Valdis->SetTalkAnimation(Textures::ValdisTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
	Valdis->setPosition(sf::Vector2f(1250, 723));
	Valdis->setInteractionPosition(sf::Vector2f(1153, 726));
	Valdis->setDialogue("Valdis");
	Valdis->setColor(sf::Color(50, 205, 50));
	Valdis->setIndex(14);
	Valdis->setProportions(sf::Vector2f(167.5, 436));
	Valdis->setscale(sf::Vector2f(0.55f, 0.55f));
	Valdis->setRightWay(false);

	Leifr->setName("Leifr");
	Leifr->setIdleAnimation(Textures::LeifrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	Leifr->SetTalkAnimation(Textures::LeifrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Leifr->setPosition(sf::Vector2f(460, 727));
	Leifr->setInteractionPosition(sf::Vector2f(650, 725));
	Leifr->setColor(sf::Color(72, 209, 204));
	Leifr->setDialogue("Leifr");
	Leifr->setIndex(14);
	Leifr->setProportions(sf::Vector2f(286, 427));
	Leifr->setscale(sf::Vector2f(0.5f, 0.5f));
	Leifr->setRightWay(false);

	Finnr->setName("Finnr");
	Finnr->setIdleAnimation(Textures::FinnrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(8));
	Finnr->SetTalkAnimation(Textures::FinnrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Finnr->setPosition(sf::Vector2f(580, 714));
	Finnr->setInteractionPosition(sf::Vector2f(650, 725));
	Finnr->setColor(sf::Color(173, 216, 230));
	Finnr->setDialogue("Finnr");
	Finnr->setIndex(14);
	Finnr->setProportions(sf::Vector2f(286, 427));
	Finnr->setscale(sf::Vector2f(0.5f, 0.5f));
	Finnr->setRightWay(false);

	Brynja->setName("Brynja");
	Brynja->setIdleAnimation(Textures::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(5));
	Brynja->SetTalkAnimation(Textures::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(600), sf::Time::Zero);
	Brynja->setColor(sf::Color(219, 0, 0));
	Brynja->setDialogue("Brynja");
	Brynja->setIndex(14);
	Brynja->setProportions(sf::Vector2f(290, 452));
	Brynja->setPosition(sf::Vector2f(1080, 711));
	Brynja->setInteractionPosition(sf::Vector2f(1050, 620));
	Brynja->setscale(sf::Vector2f(0.75f, 0.75f));
	Brynja->setRightWay(false);

	Alfr->setName("Alfr");
	Alfr->setIdleAnimation(Textures::AlfrIdle, sf::Vector2i(1, 1), sf::milliseconds(10000), sf::seconds(9999));
	Alfr->SetTalkAnimation(Textures::AlfrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Alfr->setPosition(sf::Vector2f(290, 870));
	Alfr->setInteractionPosition(sf::Vector2f(380, 885));
	Alfr->setColor(sf::Color(201, 114, 27));
	Alfr->setDialogue("Alfr");
	Alfr->setIndex(15);
	Alfr->setProportions(sf::Vector2f(204, 452));
	Alfr->setscale(sf::Vector2f(0.5f, 0.5f));
	Alfr->setRightWay(false);

	Dagny->setName("Dagny");
	Dagny->setIdleAnimation(Textures::DagnyIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(4));
	Dagny->SetTalkAnimation(Textures::DagnyTalk, sf::Vector2i(4, 1), sf::milliseconds(350), sf::Time::Zero);
	Dagny->setPosition(sf::Vector2f(1565, 705));
	Dagny->setInteractionPosition(sf::Vector2f(1680, 690));
	Dagny->setColor(sf::Color(223, 42, 193));
	Dagny->setDialogue("Dagny");
	Dagny->setIndex(15);
	Dagny->setProportions(sf::Vector2f(126, 322));
	Dagny->setscale(sf::Vector2f(0.7f, 0.7f));
	Dagny->setRightWay(false);

	Brandr->setName("Brandr");
	Brandr->setIdleAnimation(Textures::BrandrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(3.7));
	Brandr->SetTalkAnimation(Textures::BrandrTalk, sf::Vector2i(6, 1), sf::milliseconds(750), sf::Time::Zero);
	Brandr->setPosition(sf::Vector2f(800, 800));
	Brandr->setInteractionPosition(sf::Vector2f(890, 840));
	Brandr->setColor(sf::Color(255, 215, 0));
	Brandr->setDialogue("Brandr");
	Brandr->setIndex(15);
	Brandr->setProportions(sf::Vector2f(181, 525));
	Brandr->setscale(sf::Vector2f(0.45f, 0.45f));
	Brandr->setRightWay(true);

	Yngvarr->setName("Yngvarr");
	Yngvarr->setIdleAnimation(Textures::YngvarrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5.2));
	Yngvarr->SetTalkAnimation(Textures::YngvarrTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
	Yngvarr->setPosition(sf::Vector2f(900, 820));
	Yngvarr->setInteractionPosition(sf::Vector2f(1015, 832));
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
	{
		it->second->unload();
		mNpcMap.erase(it);
		it = mNpcMap.begin();
	}
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
