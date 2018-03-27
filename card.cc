#include "card.h"
#include "enchantment.h"
#include "subject.h"
#include "board.h"
#include "cardfactory.h"

using namespace std;

extern CardFactory cardFactory;
typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);
Card::Card(std::string name,std::string type,
	std::string detail, int magicCost, int targetNumEff):
		name{name},type{type},detail{detail},
		magicCost{magicCost},targetNumEff{targetNumEff}{};

Card::~Card(){}

CardType& Card::whoOwner() { return owner;}



void Card::useEnchantEffect(){
	if(getStatus().enchants.size() > 0){
		getStatus().enchants.back()->doEffect(*this);
	}
	else{ throw NoEffect{};}
}

void Card::applyEnchant(Card *c){
	newCard nc = cardFactory.getfactory()[c->getName()];
	std::unique_ptr<Card> card = (cardFactory.*nc)();
	card->setToBoard(b);
	card->equipTo(c->equipToWho());
	card->getStatus().owner = b->activePlayer().whichPlayer();
	getStatus().enchants.emplace_back(std::move(card));
	getStatus().enchants.back()->doEffect(*this);
}

void Card::removeNewestEnchant(){
	if (getStatus().enchants.size() >= 1){
		getStatus().enchants.back()->undoEffect(*this);
		getStatus().enchants.pop_back();
	}
	else{
		throw InvalidMove{"No enchantment to remove from."};
	}

}
void Card::notifyAllEnchant(){
	for (auto& n: getStatus().enchants){
		n->notify(*b);
	}
}

void Card::equipTo(Card *c){
	equiptocard = c;
}

Card * Card::equipToWho(){
	return equiptocard;
}
