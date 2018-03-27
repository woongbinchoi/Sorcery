
#include "rituallist.h"
#include "subject.h"
#include "minion.h"
using namespace std;

DarkRitual::DarkRitual():
	Ritual{"Dark Ritual","Ritual","At the start of your turn gain 1 magic",0,0}{
		getStatus().power = -1;
		getStatus().hp = 5;
		getStatus().magic = 1;
		getStatus().action = -1;
		getStatus().silence = false;
	}

void DarkRitual::doEffect(Card& target){
	if (getStatus().hp >= getStatus().magic){
		++target.getStatus().magic;
		getStatus().hp -= getStatus().magic;
	}
}
void DarkRitual::useCard(Card& target){
	DarkRitual::doEffect(target);
}
void DarkRitual::notify(Subject<State, Status> &data){


	if (getStatus().owner == b->activePlayer().whichPlayer() && data.getState().type == StateType::Start){
		DarkRitual::useCard(b->activePlayer());
	}
}
void DarkRitual::useCard(){}
void DarkRitual::doEffect(){}


AuraOfPower::AuraOfPower():
	Ritual{"Aura Of Power","Ritual","Whenever a minion enters play under your control, it gains +1/+1",1,0}{
		getStatus().power = -1;
		getStatus().hp = 4;
		getStatus().magic = 1;
		getStatus().action = -1;
		getStatus().silence = false;
	}

void AuraOfPower::doEffect(Card& target){
	if (getStatus().hp >= getStatus().magic){
		++target.getStatus().hp;
		++target.getStatus().power;
		getStatus().hp -= getStatus().magic;
	}
}
void AuraOfPower::useCard(Card& target){
	AuraOfPower::doEffect(target);
}

void AuraOfPower::notify(Subject<State, Status> &data){


	if (data.getState().type == StateType::Played && 
		data.getState().card_t == CardType::Minion &&
		getStatus().owner == b->activePlayer().whichPlayer()){
		AuraOfPower::doEffect(*(b->activePlayer().getBoardCards()[b->getStatus().pos]));
	}		
}
void AuraOfPower::useCard(){}
void AuraOfPower::doEffect(){}


Standstill::Standstill():
	Ritual{"Standstill","Ritual","Whenever a minion enters play, destroy it",
	3,0}{
		getStatus().power = -1;
		getStatus().hp = 4;
		getStatus().magic = 2;
		getStatus().action = -1;
		getStatus().silence = false;
	}

void Standstill::doEffect(Card& target){
	if (getStatus().hp >= getStatus().magic){
		b->removeCard(target);
		getStatus().hp -= getStatus().magic;
	}
}
void Standstill::useCard(Card& target){
	Standstill::doEffect(target);
}

void Standstill::notify(Subject<State, Status> &data){
	if (data.getState().type == StateType::Played &&
		data.getState().card_t == CardType::Minion){
		if (data.getState().player == CardType::Player1){
			Standstill::useCard(*(b->getPlayer1().getBoardCards()[b->getStatus().pos]));
		}
		else{
			Standstill::useCard(*(b->getPlayer2().getBoardCards()[b->getStatus().pos]));
		}
	}
}

void Standstill::useCard(){}
void Standstill::doEffect(){}
