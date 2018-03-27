#include "ritual.h"
#include "enchantment.h"
Ritual::Ritual(std::string name,std::string type,std::string detail, 
				int magicCost, int targetNumEff):
		Card{name,type,detail,magicCost,targetNumEff}{}

Ritual::~Ritual(){}

card_template_t Ritual::getDisplay() {
	return display_ritual(getName(),getMagic(),getStatus().magic,getDetail(),getStatus().hp);
}
