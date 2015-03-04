#include "NpcHandler.h"
#include "..\Logics\PathFinder.h"

#define CreateNpc mNpcMap.insert(std::make_pair

static std::map<std::string, NpcPtr> mNpcMap;

NpcHandler::NpcHandler()
{
}

void NpcHandler::load()
{
	RMI.loadResource(Font::Skranji_regular);
	RMI.loadResource(Font::Skranji_outline);

	NpcPtr Valdis(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Leifr(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Finnr(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Brynja(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Alfr(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Dagny(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Brandr(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Yngvarr(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Seagull(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Mailman(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Princess(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Beor(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr DruidLeader(new Npc(Font::Skranji_regular, Font::Skranji_outline));
	NpcPtr Druids(new Npc(Font::Skranji_regular, Font::Skranji_outline));

	Valdis->setName("Valdis");
	Valdis->setIdleAnimation(Texture::ValdisIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(7));
	Valdis->SetTalkAnimation(Texture::ValdisTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
	Valdis->setPosition(sf::Vector2f(1250, 723));
	Valdis->setInteractionPosition(sf::Vector2f(1153, 726));
	Valdis->setColor(sf::Color(50, 205, 50));
	Valdis->setIndex(14);
	Valdis->setProportions(sf::Vector2f(167.5, 436));
	Valdis->setscale(sf::Vector2f(0.55f, 0.55f));
	Valdis->setFlip(false);

	Leifr->setName("Leifr");
	Leifr->setIdleAnimation(Texture::LeifrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	Leifr->SetTalkAnimation(Texture::LeifrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Leifr->setPosition(sf::Vector2f(460, 727));
	Leifr->setInteractionPosition(sf::Vector2f(650, 725));
	Leifr->setColor(sf::Color(72, 209, 204));
	Leifr->setIndex(14);
	Leifr->setProportions(sf::Vector2f(286, 427));
	Leifr->setscale(sf::Vector2f(0.5f, 0.5f));
	Leifr->setFlip(false);

	Finnr->setName("Finnr");
	Finnr->setIdleAnimation(Texture::FinnrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(8));
	Finnr->SetTalkAnimation(Texture::FinnrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Finnr->setPosition(sf::Vector2f(580, 714));
	Finnr->setInteractionPosition(sf::Vector2f(650, 725));
	Finnr->setColor(sf::Color(173, 216, 230));
	Finnr->setIndex(14);
	Finnr->setProportions(sf::Vector2f(286, 427));
	Finnr->setscale(sf::Vector2f(0.5f, 0.5f));
	Finnr->setFlip(false);

	Brynja->setName("Brynja");
	Brynja->setIdleAnimation(Texture::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(5));
	Brynja->SetTalkAnimation(Texture::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(600), sf::Time::Zero);
	Brynja->setColor(sf::Color(219, 0, 0));
	Brynja->setIndex(14);
	Brynja->setProportions(sf::Vector2f(290, 452));
	Brynja->setPosition(sf::Vector2f(1080, 711));
	Brynja->setInteractionPosition(sf::Vector2f(1050, 620));
	Brynja->setscale(sf::Vector2f(1.f, 1.f));
	Brynja->setFlip(false);

	Alfr->setName("Alfr");
	Alfr->setIdleAnimation(Texture::AlfrIdle, sf::Vector2i(1, 1), sf::milliseconds(10000), sf::seconds(9999));
	Alfr->SetTalkAnimation(Texture::AlfrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Alfr->setPosition(sf::Vector2f(290, 870));
	Alfr->setInteractionPosition(sf::Vector2f(380, 885));
	Alfr->setColor(sf::Color(201, 114, 27));
	Alfr->setIndex(15);
	Alfr->setProportions(sf::Vector2f(204, 452));
	Alfr->setscale(sf::Vector2f(0.55f, 0.55f));
	Alfr->setFlip(false);

	Dagny->setName("Dagny");
	Dagny->setIdleAnimation(Texture::DagnyIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(4));
	Dagny->SetTalkAnimation(Texture::DagnyTalk, sf::Vector2i(4, 1), sf::milliseconds(350), sf::Time::Zero);
	Dagny->setPosition(sf::Vector2f(1565, 705));
	Dagny->setInteractionPosition(sf::Vector2f(1680, 690));
	Dagny->setColor(sf::Color(223, 42, 193));
	Dagny->setIndex(15);
	Dagny->setProportions(sf::Vector2f(126, 322));
	Dagny->setscale(sf::Vector2f(0.59f, 0.59f));
	Dagny->setFlip(false);

	Brandr->setName("Brandr");
	Brandr->setIdleAnimation(Texture::BrandrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(3.7));
	Brandr->SetTalkAnimation(Texture::BrandrTalk, sf::Vector2i(6, 1), sf::milliseconds(750), sf::Time::Zero);
	Brandr->setPosition(sf::Vector2f(800, 800));
	Brandr->setInteractionPosition(sf::Vector2f(890, 840));
	Brandr->setColor(sf::Color(255, 215, 0));
	Brandr->setIndex(15);
	Brandr->setProportions(sf::Vector2f(181, 525));
	Brandr->setscale(sf::Vector2f(0.45f, 0.45f));
	Brandr->setFlip(true);

	Yngvarr->setName("Yngvarr");
	Yngvarr->setIdleAnimation(Texture::YngvarrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5.2));
	Yngvarr->SetTalkAnimation(Texture::YngvarrTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
	Yngvarr->setPosition(sf::Vector2f(900, 820));
	Yngvarr->setInteractionPosition(sf::Vector2f(1015, 832));
	Yngvarr->setColor(sf::Color(176, 196, 222));
	Yngvarr->setIndex(15);
	Yngvarr->setProportions(sf::Vector2f(148, 472));
	Yngvarr->setscale(sf::Vector2f(0.55f, 0.55f));
	Yngvarr->setFlip(false);

	Seagull->setName("Bosse");
	Seagull->setIdleAnimation(Texture::SeagullIdle, sf::Vector2i(4, 2), sf::milliseconds(800), sf::seconds(7));
	Seagull->SetTalkAnimation(Texture::SeagullTalk, sf::Vector2i(2, 1), sf::milliseconds(650), sf::Time::Zero);
	Seagull->setPosition(sf::Vector2f(1800, 460));
	Seagull->setInteractionPosition(sf::Vector2f(1650, 500));
	Seagull->setColor(sf::Color(176, 196, 222));
	Seagull->setDialogue("Bosse_Beach");
	Seagull->setIndex(15);
	Seagull->setProportions(sf::Vector2f(124, 164));
	Seagull->setscale(sf::Vector2f(0.55f, 0.55f));
	Seagull->setFlip(false);

	Mailman->setName("Mailman");
	Mailman->setIdleAnimation(Texture::MailManSadIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Mailman->SetTalkAnimation(Texture::MailManSadTalk, sf::Vector2i(4, 1), sf::milliseconds(550), sf::Time::Zero);
	Mailman->setPosition(sf::Vector2f(820, 1000));
	Mailman->setInteractionPosition(sf::Vector2f(700, 1000));
	Mailman->setColor(sf::Color(176, 196, 222));
	Mailman->setIndex(19);
	Mailman->setProportions(sf::Vector2f(199, 432));
	Mailman->setscale(sf::Vector2f(0.55f, 0.55f));
	Mailman->setFlip(false);

	Princess->setName("Girl");
	Princess->setIdleAnimation(Texture::PrincessIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Princess->SetTalkAnimation(Texture::PrincessTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Princess->setPosition(sf::Vector2f(240, 920));
	Princess->setInteractionPosition(sf::Vector2f(415, 990));
	Princess->setColor(sf::Color(176, 196, 222));
	Princess->setIndex(7);
	Princess->setProportions(sf::Vector2f(266, 273));
	Princess->setscale(sf::Vector2f(0.40f, 0.40f));
	Princess->setFlip(false);

	Beor->setName("Beor");
	Beor->setIdleAnimation(Texture::BeorIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Beor->SetTalkAnimation(Texture::BeorTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Beor->setPosition(sf::Vector2f(450, 790));
	Beor->setInteractionPosition(sf::Vector2f(700, 780));
	Beor->setColor(sf::Color(176, 196, 222));
	Beor->setIndex(3);
	Beor->setProportions(sf::Vector2f(243, 558));
	Beor->setscale(sf::Vector2f(0.65f, 0.65f));
	Beor->setFlip(true);

	DruidLeader->setName("Druid Leader");
	DruidLeader->setIdleAnimation(Texture::DruidLeaderIdle, sf::Vector2i(1, 1), sf::milliseconds(0), sf::seconds(999));
	DruidLeader->SetTalkAnimation(Texture::DruidLeaderTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	DruidLeader->setPosition(sf::Vector2f(650, 790));
	DruidLeader->setInteractionPosition(sf::Vector2f(700, 780));
	DruidLeader->setColor(sf::Color(176, 196, 222));
	DruidLeader->setIndex(3);
	DruidLeader->setProportions(sf::Vector2f(243, 558));
	DruidLeader->setscale(sf::Vector2f(0.65f, 0.65f));
	DruidLeader->setFlip(false);

	Druids->setName("Druids");
	Druids->setPosition(sf::Vector2f(0, 450));
	Druids->setInvisibleRect(sf::Vector2f(565, 630));
	Druids->setColor(sf::Color(176, 196, 222));
	Druids->setIsInvisble(true);

	CreateNpc("Valdis", std::move(Valdis)));
	CreateNpc("Leifr", std::move(Leifr)));
	CreateNpc("Finnr", std::move(Finnr)));
	CreateNpc("Brynja", std::move(Brynja)));
	CreateNpc("Alfr", std::move(Alfr)));
	CreateNpc("Dagny", std::move(Dagny)));
	CreateNpc("Brandr", std::move(Brandr)));
	CreateNpc("Yngvarr", std::move(Yngvarr)));
	CreateNpc("Seagull", std::move(Seagull)));
	CreateNpc("Mailman", std::move(Mailman)));
	CreateNpc("Princess", std::move(Princess)));
	CreateNpc("Beor", std::move(Beor)));
	CreateNpc("DruidLeader", std::move(DruidLeader)));
	CreateNpc("Druids", std::move(Druids)));
}

void NpcHandler::unload()
{
	RMI.unloadResource(Font::Skranji_regular);
	RMI.unloadResource(Font::Skranji_outline);
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
