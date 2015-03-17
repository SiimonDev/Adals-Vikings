#include "NpcHandler.h"
#include "..\Logics\PathFinder.h"

#define CreateNpc mNpcMap.insert(std::make_pair

NpcHandler::NpcHandler()
{
}

NpcHandler &NpcHandler::getInstance()
{
	static NpcHandler instance;
	return instance;
}

void NpcHandler::load()
{
	RMI.loadResource(Font::Skranji_regular);

	NpcPtr Valdis(new Npc(Font::Skranji_regular));
	NpcPtr Leifr(new Npc(Font::Skranji_regular));
	NpcPtr Finnr(new Npc(Font::Skranji_regular));
	NpcPtr Brynja(new Npc(Font::Skranji_regular));
	NpcPtr Alfr(new Npc(Font::Skranji_regular));
	NpcPtr Dagny(new Npc(Font::Skranji_regular));
	NpcPtr Brandr(new Npc(Font::Skranji_regular));
	NpcPtr Yngvarr(new Npc(Font::Skranji_regular));
	NpcPtr Seagull(new Npc(Font::Skranji_regular));
	NpcPtr Mailman(new Npc(Font::Skranji_regular));
	NpcPtr Princess(new Npc(Font::Skranji_regular));
	NpcPtr Beor(new Npc(Font::Skranji_regular));
	NpcPtr Druids(new Npc(Font::Skranji_regular));
	NpcPtr DruidLeader(new Npc(Font::Skranji_regular));
	NpcPtr HipsterDruid(new Npc(Font::Skranji_regular));
	NpcPtr Druid2(new Npc(Font::Skranji_regular));
	NpcPtr Druid3(new Npc(Font::Skranji_regular));
	NpcPtr Druid4(new Npc(Font::Skranji_regular));
	NpcPtr Dennis(new Npc(Font::Skranji_regular));
	NpcPtr HiddenLeifr(new Npc(Font::Skranji_regular));
	NpcPtr Guard(new Npc(Font::Skranji_regular));
	NpcPtr Aethelberth(new Npc(Font::Skranji_regular));
	NpcPtr Cerdic(new Npc(Font::Skranji_regular));
	NpcPtr Leofstan(new Npc(Font::Skranji_regular));
	NpcPtr Miner(new Npc(Font::Skranji_regular));
	NpcPtr Osgar(new Npc(Font::Skranji_regular));
	NpcPtr Jacob(new Npc(Font::Skranji_regular));
	NpcPtr Parrik(new Npc(Font::Skranji_regular));


	Valdis->setName("Valdis");
	Valdis->setIdleAnimation(Texture::ValdisIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(7));
	Valdis->SetTalkAnimation(Texture::ValdisTalk, sf::Vector2i(2, 1), sf::milliseconds(400), sf::Time::Zero);
	Valdis->setPosition(sf::Vector2f(1250, 723));
	Valdis->setInteractionPosition(sf::Vector2f(1153, 726));
	Valdis->setColor(sf::Color(50, 205, 50));
	Valdis->setIndex(14);
	Valdis->setScale(sf::Vector2f(0.55f, 0.55f));
	Valdis->setFlip(false);

	Leifr->setName("Leifr");
	Leifr->setIdleAnimation(Texture::LeifrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5));
	Leifr->SetTalkAnimation(Texture::LeifrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Leifr->setPosition(sf::Vector2f(460, 727));
	Leifr->setInteractionPosition(sf::Vector2f(650, 725));
	Leifr->setColor(sf::Color(72, 209, 204));
	Leifr->setIndex(14);
	Leifr->setScale(sf::Vector2f(0.4f, 0.4f));
	Leifr->setFlip(false);

	Finnr->setName("Finnr");
	Finnr->setIdleAnimation(Texture::FinnrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(8));
	Finnr->SetTalkAnimation(Texture::FinnrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Finnr->setPosition(sf::Vector2f(580, 714));
	Finnr->setInteractionPosition(sf::Vector2f(650, 725));
	Finnr->setColor(sf::Color(173, 216, 230));
	Finnr->setIndex(14);
	Finnr->setScale(sf::Vector2f(0.5f, 0.5f));
	Finnr->setFlip(false);

	Brynja->setName("Brynja");
	Brynja->setIdleAnimation(Texture::BrynjaIdle, sf::Vector2i(2, 1), sf::milliseconds(350), sf::seconds(5));
	Brynja->SetTalkAnimation(Texture::BrynjaTalk, sf::Vector2i(4, 1), sf::milliseconds(600), sf::Time::Zero);
	Brynja->setColor(sf::Color(219, 0, 0));
	Brynja->setIndex(14);
	Brynja->setPosition(sf::Vector2f(1080, 711));
	Brynja->setInteractionPosition(sf::Vector2f(1050, 620));
	Brynja->setScale(sf::Vector2f(1.f, 1.f));
	Brynja->setFlip(false);

	Alfr->setName("Alfr");
	Alfr->setIdleAnimation(Texture::AlfrIdle, sf::Vector2i(1, 1), sf::milliseconds(10000), sf::seconds(9999));
	Alfr->SetTalkAnimation(Texture::AlfrTalk, sf::Vector2i(2, 1), sf::milliseconds(350), sf::Time::Zero);
	Alfr->setPosition(sf::Vector2f(290, 870));
	Alfr->setInteractionPosition(sf::Vector2f(380, 885));
	Alfr->setColor(sf::Color(201, 114, 27));
	Alfr->setIndex(15);
	Alfr->setScale(sf::Vector2f(0.55f, 0.55f));
	Alfr->setFlip(false);

	Dagny->setName("Dagny");
	Dagny->setIdleAnimation(Texture::DagnyIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(4));
	Dagny->SetTalkAnimation(Texture::DagnyTalk, sf::Vector2i(4, 1), sf::milliseconds(450), sf::Time::Zero);
	Dagny->setPosition(sf::Vector2f(1565, 705));
	Dagny->setInteractionPosition(sf::Vector2f(1680, 690));
	Dagny->setColor(sf::Color(223, 42, 193));
	Dagny->setIndex(15);
	Dagny->setScale(sf::Vector2f(0.59f, 0.59f));
	Dagny->setFlip(false);

	Brandr->setName("Brandr");
	Brandr->setIdleAnimation(Texture::BrandrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(3.7));
	Brandr->SetTalkAnimation(Texture::BrandrTalk, sf::Vector2i(6, 1), sf::milliseconds(750), sf::Time::Zero);
	Brandr->setPosition(sf::Vector2f(800, 800));
	Brandr->setInteractionPosition(sf::Vector2f(890, 840));
	Brandr->setColor(sf::Color(255, 215, 0));
	Brandr->setIndex(15);
	Brandr->setScale(sf::Vector2f(0.45f, 0.45f));
	Brandr->setFlip(true);

	Yngvarr->setName("Yngvarr");
	Yngvarr->setIdleAnimation(Texture::YngvarrIdle, sf::Vector2i(2, 1), sf::milliseconds(400), sf::seconds(5.2));
	Yngvarr->SetTalkAnimation(Texture::YngvarrTalk, sf::Vector2i(4, 1), sf::milliseconds(650), sf::Time::Zero);
	Yngvarr->setPosition(sf::Vector2f(900, 820));
	Yngvarr->setInteractionPosition(sf::Vector2f(1015, 832));
	Yngvarr->setColor(sf::Color(176, 196, 222));
	Yngvarr->setIndex(15);
	Yngvarr->setScale(sf::Vector2f(0.55f, 0.55f));
	Yngvarr->setFlip(false);

	Seagull->setName("Bosse");
	Seagull->setIdleAnimation(Texture::SeagullIdle, sf::Vector2i(4, 2), sf::milliseconds(800), sf::seconds(7));
	Seagull->SetTalkAnimation(Texture::SeagullTalk, sf::Vector2i(2, 1), sf::milliseconds(650), sf::Time::Zero);
	Seagull->setPosition(sf::Vector2f(1800, 460));
	Seagull->setInteractionPosition(sf::Vector2f(1650, 500));
	Seagull->setColor(sf::Color(176, 196, 222));
	Seagull->setDialogue("Bosse_Beach");
	Seagull->setIndex(15);
	Seagull->setScale(sf::Vector2f(0.55f, 0.55f));
	Seagull->setFlip(false);

	Mailman->setName("Mailman");
	Mailman->setIdleAnimation(Texture::MailManSadIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Mailman->SetTalkAnimation(Texture::MailManSadTalk, sf::Vector2i(4, 1), sf::milliseconds(550), sf::Time::Zero);
	Mailman->setPosition(sf::Vector2f(820, 1000));
	Mailman->setInteractionPosition(sf::Vector2f(700, 1000));
	Mailman->setColor(sf::Color(176, 196, 222));
	Mailman->setIndex(19);
	Mailman->setScale(sf::Vector2f(0.55f, 0.55f));
	Mailman->setFlip(false);

	Princess->setName("Girl");
	Princess->setIdleAnimation(Texture::PrincessIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Princess->SetTalkAnimation(Texture::PrincessTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Princess->setPosition(sf::Vector2f(240, 920));
	Princess->setInteractionPosition(sf::Vector2f(415, 990));
	Princess->setColor(sf::Color(176, 196, 222));
	Princess->setIndex(7);
	Princess->setScale(sf::Vector2f(0.40f, 0.40f));
	Princess->setFlip(false);

	Beor->setName("Beor");
	Beor->setIdleAnimation(Texture::BeorIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Beor->SetTalkAnimation(Texture::BeorTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Beor->setPosition(sf::Vector2f(450, 790));
	Beor->setInteractionPosition(sf::Vector2f(700, 780));
	Beor->setColor(sf::Color(176, 196, 222));
	Beor->setIndex(3);
	Beor->setScale(sf::Vector2f(0.65f, 0.65f));
	Beor->setFlip(true);

	Guard->setName("Guard");
	Guard->setIdleAnimation(Texture::GuardIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Guard->SetTalkAnimation(Texture::GuardTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Guard->setPosition(sf::Vector2f(965, 730));
	Guard->setInteractionPosition(sf::Vector2f(1095, 730));
	Guard->setColor(sf::Color(176, 196, 222));
	Guard->setIndex(3);
	Guard->setScale(sf::Vector2f(0.6f, 0.6f));
	Guard->setFlip(false);

	Aethelberth->setName("Aethelberth");
	Aethelberth->setIdleAnimation(Texture::AethelberthIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(7));
	Aethelberth->SetTalkAnimation(Texture::AethelberthTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Aethelberth->setPosition(sf::Vector2f(590, 760));
	Aethelberth->setInteractionPosition(sf::Vector2f(770, 750));
	Aethelberth->setColor(sf::Color(176, 196, 222));
	Aethelberth->setIndex(12);
	Aethelberth->setScale(sf::Vector2f(0.55f, 0.55f));
	Aethelberth->setFlip(false);

	Cerdic->setName("Cerdic");
	Cerdic->setIdleAnimation(Texture::CerdicIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(3.5));
	Cerdic->SetTalkAnimation(Texture::CerdicTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Cerdic->setPosition(sf::Vector2f(270, 855));
	Cerdic->setInteractionPosition(sf::Vector2f(420, 850));
	Cerdic->setColor(sf::Color(176, 196, 222));
	Cerdic->setIndex(3);
	Cerdic->setScale(sf::Vector2f(0.65f, 0.65f));
	Cerdic->setFlip(false);

	Leofstan->setName("Leofstan");
	Leofstan->setIdleAnimation(Texture::LeofstanIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(10));
	Leofstan->SetTalkAnimation(Texture::LeofstanTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Leofstan->setPosition(sf::Vector2f(162, 625));
	Leofstan->setInteractionPosition(sf::Vector2f(310, 620));
	Leofstan->setColor(sf::Color(176, 196, 222));
	Leofstan->setIndex(4);
	Leofstan->setScale(sf::Vector2f(0.65f, 0.65f));
	Leofstan->setFlip(false);

	Miner->setName("Miner");
	Miner->setIdleAnimation(Texture::MinerIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Miner->SetTalkAnimation(Texture::MinerTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Miner->setPosition(sf::Vector2f(700, 890));
	Miner->setInteractionPosition(sf::Vector2f(950, 860));
	Miner->setColor(sf::Color(176, 196, 222));
	Miner->setIndex(8);
	Miner->setScale(sf::Vector2f(0.7f, 0.7f));
	Miner->setFlip(false);

	Osgar->setName("Osgar");
	Osgar->setIdleAnimation(Texture::OsgarIdle, sf::Vector2i(2, 1), sf::milliseconds(300), sf::seconds(5));
	Osgar->SetTalkAnimation(Texture::OsgarTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	Osgar->setPosition(sf::Vector2f(300, 570));
	Osgar->setInteractionPosition(sf::Vector2f(440, 575));
	Osgar->setColor(sf::Color(176, 196, 222));
	Osgar->setIndex(3);
	Osgar->setScale(sf::Vector2f(0.4f, 0.4f));
	Osgar->setFlip(false);

	DruidLeader->setName("Druid Leader");
	DruidLeader->setIdleAnimation(Texture::DruidLeaderIdle, sf::Vector2i(1, 1), sf::milliseconds(0), sf::seconds(999));
	DruidLeader->SetTalkAnimation(Texture::DruidLeaderTalk, sf::Vector2i(2, 1), sf::milliseconds(450), sf::Time::Zero);
	DruidLeader->setPosition(sf::Vector2f(650, 790));
	DruidLeader->setInteractionPosition(sf::Vector2f(820, 770));
	DruidLeader->setColor(sf::Color(176, 196, 222));
	DruidLeader->setIndex(3);
	DruidLeader->setScale(sf::Vector2f(1.f, 1.f));
	DruidLeader->setFlip(false);

	Druids->setName("Druids");
	Druids->setPosition(sf::Vector2f(0, 400));
	Druids->setInvisibleRect(sf::Vector2f(430, 100));
	Druid3->setInteractionPosition(sf::Vector2f(811, 726));
	Druids->setColor(sf::Color(176, 196, 222));
	Druids->setIsInvisble(true);

	HipsterDruid->setName("Hipster Druid");
	HipsterDruid->setPosition(sf::Vector2f(0, 510));
	HipsterDruid->setInvisibleRect(sf::Vector2f(120, 230));
	HipsterDruid->setInteractionPosition(sf::Vector2f(811, 726));
	HipsterDruid->setColor(sf::Color(176, 196, 222));
	HipsterDruid->setIsInvisble(true);

	Druid2->setName("Irish Druid");
	Druid2->setPosition(sf::Vector2f(405, 510));
	Druid2->setInvisibleRect(sf::Vector2f(125, 116));
	Druid2->setInteractionPosition(sf::Vector2f(811, 726));
	Druid2->setColor(sf::Color(176, 196, 222));
	Druid2->setIsInvisble(true);

	Druid3->setName("Socially Awkward Druid");
	Druid3->setPosition(sf::Vector2f(133, 490));
	Druid3->setInvisibleRect(sf::Vector2f(103, 150));
	Druid3->setInteractionPosition(sf::Vector2f(811, 726));
	Druid3->setColor(sf::Color(176, 196, 222));
	Druid3->setIsInvisble(true);

	Druid4->setName("Handsome Druid");
	Druid4->setPosition(sf::Vector2f(120, 850));
	Druid4->setInvisibleRect(sf::Vector2f(150, 182));
	Druid4->setInteractionPosition(sf::Vector2f(811, 726));
	Druid4->setColor(sf::Color(176, 196, 222));
	Druid4->setIsInvisble(true);

	Dennis->setName("Dennis");
	Dennis->setPosition(sf::Vector2f(440, 680));
	Dennis->setInvisibleRect(sf::Vector2f(150, 220));
	Dennis->setInteractionPosition(sf::Vector2f(811, 726));
	Dennis->setColor(sf::Color(176, 196, 222));
	Dennis->setIsInvisble(true);

	HiddenLeifr->setName("Leifr");
	HiddenLeifr->setPosition(sf::Vector2f(440, 680));
	HiddenLeifr->setInvisibleRect(sf::Vector2f(40, 80));
	HiddenLeifr->setInteractionPosition(sf::Vector2f(811, 726));
	HiddenLeifr->setColor(sf::Color(176, 196, 222));
	HiddenLeifr->setIsInvisble(true);

	Jacob->setName("Jacob");
	Jacob->setPosition(sf::Vector2f(190, 365));
	Jacob->setInvisibleRect(sf::Vector2f(90, 135));
	Jacob->setInteractionPosition(sf::Vector2f(205, 530));
	Jacob->setColor(sf::Color(176, 196, 222));
	Jacob->setIsInvisble(true);

	Parrik->setName("Parrik");
	Parrik->setPosition(sf::Vector2f(715, 355));
	Parrik->setInvisibleRect(sf::Vector2f(55, 175));
	Parrik->setInteractionPosition(sf::Vector2f(700, 520));
	Parrik->setColor(sf::Color(176, 196, 222));
	Parrik->setIsInvisble(true);

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
	CreateNpc("Hipster druid", std::move(HipsterDruid)));
	CreateNpc("Dennis", std::move(Dennis)));
	CreateNpc("Druid2", std::move(Druid2)));
	CreateNpc("Druid3", std::move(Druid3)));
	CreateNpc("Druid4", std::move(Druid4)));
	CreateNpc("HiddenLeifr", std::move(HiddenLeifr)));
	CreateNpc("Guard", std::move(Guard)));
	CreateNpc("Aethelberth", std::move(Aethelberth)));
	CreateNpc("Cerdic", std::move(Cerdic)));
	CreateNpc("Leofstan", std::move(Leofstan)));
	CreateNpc("Miner", std::move(Miner)));
	CreateNpc("Osgar", std::move(Osgar)));
	CreateNpc("Jacob", std::move(Jacob)));
	CreateNpc("Parrik", std::move(Parrik)));
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
