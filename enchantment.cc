#include "enchantment.h"

Enchantment::Enchantment(std::string name,std::string type,
				std::string detail,int magicCost, int targetNumEff):
	Card{name,type,detail,magicCost,targetNumEff}{}


Enchantment::~Enchantment(){}
