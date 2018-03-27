#include "spelllist.h"
#include "board.h"
#include "ritual.h"
#include "minion.h"
#include "cardfactory.h"

typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);
extern CardFactory cardFactory;

using namespace std;

//Banish
Banish::Banish():
	Spell{"Banish","Spell","Destroy target minion or ritual",2,1}{		
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void Banish::doEffect(Card &target){
	target.getStatus().hp = 0;
}
void Banish::useCard(Card &target){
		Banish::doEffect(target);
}
void Banish::doEffect(){}
void Banish::useCard(){}


//Unsummon
Unsummon::Unsummon():
	Spell{"Unsummon","Spell","Return target minion to its owner's hand",1,1}{
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void Unsummon::doEffect(Card &target){
	if (target.whoOwner() == CardType::Player1 && b->getPlayer1().getHand().size() < 5){
		b->returnCard(target);
	}
	else if (target.whoOwner() == CardType::Player2 && b->getPlayer2().getHand().size() < 5){
		b->returnCard(target);
	}
	else{
		throw Exception{"Owner of this minion's hand is full!"};
	}
}
void Unsummon::useCard(Card &target){
	Unsummon::doEffect(target);
}
void Unsummon::doEffect(){}
void Unsummon::useCard(){}

//Recharge
Recharge::Recharge():
	Spell{"Recharge","Spell","Your ritual gains 3 charges",1,0}{
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void Recharge::doEffect(Card &target){
	target.getStatus().hp += 3;
}
void Recharge::useCard(){
	if (b->activePlayer().getRitualCard()->getType() == "Ritual"){
		Recharge::doEffect(*b->activePlayer().getRitualCard());
	}
}
void Recharge::doEffect(){}
void Recharge::useCard(Card &target){}

Disenchant::Disenchant():
	Spell{"Disenchant","Spell","Destroy the top enchantment on target minion",1,1}{
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void Disenchant::doEffect(Card &target){
	target.removeNewestEnchant();
}
void Disenchant::useCard(Card &target){
	Disenchant::doEffect(target);
}
void Disenchant::doEffect(){}
void Disenchant::useCard(){}

RaiseDead::RaiseDead():
	Spell{"Raise Dead","Spell","Resurrect the top minion in your graveyard and set its defence to 1",1,0}{
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void RaiseDead::doEffect(Card &target){}
void RaiseDead::useCard(){
	if (b->activePlayer().getGraveyard().size() >= 1 &&
		!b->activePlayer().isBoardFull()){
		newCard nc = cardFactory.getfactory()[b->activePlayer().getGraveyard().back()->getName()];
		std::unique_ptr<Card> c = (cardFactory.*nc)();
		c->getStatus().hp = 1;
		c->getStatus().owner = b->activePlayer().whichPlayer();
		c->setToBoard(b);
		b->playCard(std::move(c));
		b->activePlayer().getGraveyard().pop_back();
		//b->update()
		//b->update(target);
	}
	else{
		throw InvalidMove{"Graveyard is empty and/or field is full"};
	}
}
void RaiseDead::useCard(Card& target){}
void RaiseDead::doEffect(){}

Blizzard::Blizzard():
	Spell{"Blizzard","Spell","Deal 2 damage to all minions",3,0}{
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void Blizzard::doEffect(Card &target){
	target.getStatus().hp -= 2;
}
void Blizzard::useCard(){
	for (int i = 0; i < 5; ++i){
		if (b->activePlayer().getBoardCards()[i]->getType() != ""){
			Blizzard::doEffect(*b->activePlayer().getBoardCards()[i]);
		}
	}
	for (int i = 0; i < 5; ++i){
		if (b->nonactivePlayer().getBoardCards()[i]->getType() != ""){
			Blizzard::doEffect(*b->nonactivePlayer().getBoardCards()[i]);
		}
	}
}
void Blizzard::useCard(Card& target){}
void Blizzard::doEffect(){}


Refresh::Refresh():
	Spell{"Refresh","Spell","Recovers 2 Health",1,0}{
		getStatus().power = -1;
		getStatus().hp = -1;
		getStatus().magic = -1;
		getStatus().action = -1;
		getStatus().silence = false;
	}
void Refresh::doEffect(Card &target){
}
void Refresh::useCard(){
	b->activePlayer().getStatus().hp += 2;
}
void Refresh::useCard(Card& target){}
void Refresh::doEffect(){}



		

