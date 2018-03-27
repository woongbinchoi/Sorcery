#include "spell.h"

Spell::Spell(std::string name, std::string type, 
	std:: string detail, int magicCost, int targetNumEff):
	Card{name,type,detail,magicCost,targetNumEff}{}

Spell::~Spell(){}

card_template_t Spell::getDisplay() {
	return display_spell(getName(),getMagic(),getDetail());
}

