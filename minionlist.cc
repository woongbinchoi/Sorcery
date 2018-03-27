#include "minionlist.h"
#include "cardfactory.h"
#include "exceptions.h"
#include <memory>

using namespace std;

typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);
extern CardFactory cardFactory;

AirElemental::AirElemental():
	Minion{"Air Elemental","Minion","",0,0}{
		getStatus().power = 1;
		getStatus().hp = 1;
		getStatus().magic = 0;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void AirElemental::doEffect(){};
void AirElemental::doEffect(Card &target){};
card_template_t AirElemental::getDisplay() {
	return display_minion_no_ability(getName(),getMagic(),getStatus().power,getStatus().hp);
}

EarthElemental::EarthElemental():
	Minion{"Earth Elemental","Minion","",3,0}{
		getStatus().power = 4;
		getStatus().hp = 4;
		getStatus().magic = 0;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void EarthElemental::doEffect(){};
void EarthElemental::doEffect(Card &target){};
card_template_t EarthElemental::getDisplay() {
	return display_minion_no_ability(getName(),getMagic(),getStatus().power,getStatus().hp);
}

BoneGolem::BoneGolem():
	Minion{"Bone Golem","Minion",
	"Gain +1/+1 whenever a minion leaves play.",2,0}{
		getStatus().power = 1;
		getStatus().hp = 3;
		getStatus().magic = 0;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void BoneGolem::doEffect(){
	if(!getStatus().silence){
			++getStatus().hp;
			++getStatus().power;
	}
}
void BoneGolem::notify(Subject<State, Status> &data){
	if (data.getState().type == StateType::Remove && 
		data.getState().card_t == CardType::Minion){
		BoneGolem::doEffect();
	}
}
void BoneGolem::doEffect(Card &target){};
card_template_t BoneGolem::getDisplay() {
	return display_minion_triggered_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getDetail());
}

FireElemental::FireElemental():
	Minion{"Fire Elemental","Minion",
	"Whenever an opponent's minion enter play, deal 1 damage to it.",2,0}{
		getStatus().power = 2;
		getStatus().hp = 2;  
		getStatus().magic = 0;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void FireElemental::doEffect(Card& target){
	if(!getStatus().silence){
		--target.getStatus().hp;
	}
}
void FireElemental::notify(Subject<State, Status> &data){
	if (data.getState().player != whoOwner() &&
		data.getState().type == StateType::Played &&
		data.getState().card_t == CardType::Minion){
		FireElemental::doEffect(*(b->activePlayer().getBoardCards()[b->getStatus().pos]));
	}
}
void FireElemental::doEffect(){}
card_template_t FireElemental::getDisplay() {
	return display_minion_triggered_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getDetail());
}

PotionSeller::PotionSeller():
	Minion{"Potion Seller","Minion",
	"At the end of your turn, all minions gain +0/+1.",2,0}{
		getStatus().power = 1;
		getStatus().hp = 3;
		getStatus().magic = 0;
		getStatus().action = 0;
		getStatus().silence = false;
	}

void PotionSeller::doEffect(Card& target){
	if (!getStatus().silence){
		++target.getStatus().hp;
	}
}
void PotionSeller::doEffect(){}
void PotionSeller::notify(Subject<State, Status> &data){
	if(data.getState().type == StateType::End &&
		data.getState().player == whoOwner()){
		for(auto& n: b->activePlayer().getBoardCards()){
			PotionSeller::doEffect(*n);
		}
	}
}
card_template_t PotionSeller::getDisplay() {
	return display_minion_triggered_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getDetail());
}

NovicePyromancer::NovicePyromancer():	
	Minion{"Novice Pyromancer","Minion",
	"Deal 1 damage to target minion",1,1}{
		getStatus().power = 0;
		getStatus().hp = 1;
		getStatus().magic = 1;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void NovicePyromancer::doEffect(Card& target){
		--target.getStatus().hp;		
}
void NovicePyromancer::doEffect(){}
card_template_t NovicePyromancer::getDisplay() {
	return display_minion_activated_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getStatus().magic,getDetail());
}


ApprenticeSummoner::ApprenticeSummoner():
	Minion{"Apprentice Summoner","Minion",
	"Summon a 1/1 air elemental",1,0}{
		getStatus().power = 1;
		getStatus().hp = 1;
		getStatus().magic = 1;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void ApprenticeSummoner::doEffect(){
	if (b->activePlayer().getMinionsOnField() < 5){
		newCard nc = cardFactory.getfactory()["Air Elemental"];
		std::unique_ptr<Card> c = (cardFactory.*nc)();
		c->setToBoard(b);
		c->getStatus().owner = b->activePlayer().whichPlayer();
		b->playCard(std::move(c)); // need to use std::move 
	}
	else{
		throw Exception{"Not enough Magic"};
	}
}
void ApprenticeSummoner::doEffect(Card &target){}
card_template_t ApprenticeSummoner::getDisplay() {
	return display_minion_activated_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getStatus().magic,getDetail());
}

MasterSummoner::MasterSummoner():
	Minion{"Master Summoner","Minion",
	"Summon up to three 1/1 air elementals",3,0}{
		getStatus().power = 2;
		getStatus().hp = 3;
		getStatus().magic = 2;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void MasterSummoner::doEffect(){
	if (b->activePlayer().getMinionsOnField() < 5){
		for(int i = 0; i < 3; ++i){
			if(b->activePlayer().getMinionsOnField() == 5) break;
			newCard nc = cardFactory.getfactory()["Air Elemental"];
			std::unique_ptr<Card> c = (cardFactory.*nc)();
			c->setToBoard(b);
			c->getStatus().owner = b->activePlayer().whichPlayer();
			//std::unique_ptr<Card> c = nc();
			b->playCard(std::move(c)); // need to use std::move
			}
	}
	else{
		throw Exception{"Not enough Magic"};
	}
}
void MasterSummoner::doEffect(Card &target){}
card_template_t MasterSummoner::getDisplay() {
	return display_minion_activated_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getStatus().magic,getDetail());
}

// other  cards

BountyHunter::BountyHunter():
	Minion{"Bounty Hunter","Minion",
	"Gain 1 magic whenever this card attacks, Gain 2 if it deals a killing blow",4,0}{
		getStatus().power = 1;
		getStatus().hp = 5;
		getStatus().magic = 0;
		getStatus().action = 0;
		getStatus().silence = false;
	}
void BountyHunter::useCard(Card &target){
	target.getStatus().hp -= getStatus().power;
	getStatus().hp -= target.getStatus().power;
	if (target.getStatus().hp <= 0){
		b->activePlayer().getStatus().magic += 2;
	}
	else{
		b->activePlayer().getStatus().magic += 1;
	}
}
card_template_t BountyHunter::getDisplay(){
	return display_minion_triggered_ability(getName(),getMagic(),getStatus().power,getStatus().hp,getDetail());
}

void BountyHunter::doEffect(){};
void BountyHunter::doEffect(Card &target){};

