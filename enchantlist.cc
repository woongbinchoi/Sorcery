#include "enchantlist.h"
#include "minion.h"
#include "subject.h"
//Giant Strength
GiantStrength::GiantStrength():
	Enchantment{"Giant Strength","Enchantment","",1,1}{}
void GiantStrength::doEffect(Card &target){
	target.getStatus().hp += 2;
	target.getStatus().power += 2;
}
void GiantStrength::useCard(Card &target){
	target.applyEnchant(this);
}
void GiantStrength::doEffect(){}
void GiantStrength::useCard(){}
card_template_t GiantStrength::getDisplay() {
	return display_enchantment_attack_defence(getName(),getMagic(),getDetail(),"+2","+2");
}
void GiantStrength::undoEffect(Card &target){
	target.getStatus().hp -= 2;
	target.getStatus().power -= 2;
	if (target.getStatus().power < 0){
		target.getStatus().power = 0;
	}
}

//Enrage
Enrage::Enrage():
	Enchantment{"Enrage","Enchantment","",2,1}{}
void Enrage::doEffect(Card &target){
	target.getStatus().hp *= 2;
	target.getStatus().power *= 2;
}
void Enrage::useCard(Card &target){
	target.applyEnchant(this);
}
void Enrage::doEffect(){}
void Enrage::useCard(){}
void Enrage::undoEffect(Card &target){
	target.getStatus().hp /= 2;
	target.getStatus().power /= 2;
}

card_template_t Enrage::getDisplay() {
	return display_enchantment_attack_defence(getName(),getMagic(),getDetail(),"*2","*2");
}
//Haste

Haste::Haste():
	Enchantment{"Haste","Enchantment",
	"Enchanted Minion gains +1 action each turn",1,1}{}
void Haste::doEffect(Card &target){
	++target.getStatus().action;
}
void Haste::notify(Subject<State, Status> &data){
	if (data.getState().type == StateType::Start &&
		getStatus().owner == b->activePlayer().whichPlayer()){
		doEffect(*equipToWho());
	}
}
void Haste::useCard(Card &target){
	target.applyEnchant(this);
}
void Haste::useCard(){}
void Haste::doEffect(){}
void Haste::undoEffect(Card &target){
}

card_template_t Haste::getDisplay() {
	return display_enchantment(getName(),getMagic(),getDetail());
}


//MagicFatigue
MagicFatigue::MagicFatigue():
	Enchantment{"Magic Fatigue","Enchantment",
	"Enchanted minion's activated ability costs 2 more",0,1}{}
void MagicFatigue::doEffect(Card &target){
	if (target.getStatus().magic > 0){
		target.getStatus().magic += 2;
	}
	else{
		throw InvalidMove{"This minion does not have an activated ability"};
	}
}
void MagicFatigue::useCard(Card &target){
	target.applyEnchant(this);
}
void MagicFatigue::useCard(){}
void MagicFatigue::doEffect(){}
void MagicFatigue::undoEffect(Card &target){
	if (target.getStatus().magic >= 2){
		target.getStatus().magic -= 2;
	}
	else{
		target.getStatus().magic = 2;
	}
	
}
card_template_t MagicFatigue::getDisplay() {
	return display_enchantment(getName(),getMagic(),getDetail());
}

//Silence
Silence::Silence():
	Enchantment{"Silence","Enchantment",
	"Enchanted minion cannot use abilities",1,1}{}

void Silence::doEffect(Card &target){
	target.getStatus().silence = true;
}

void Silence::useCard(Card& target){
	target.applyEnchant(this);
}

void Silence::useCard(){}
void Silence::doEffect(){}
void Silence::undoEffect(Card &target){
	target.getStatus().silence = false;
	
}
card_template_t Silence::getDisplay() {
	return display_enchantment(getName(),getMagic(),getDetail());
}





