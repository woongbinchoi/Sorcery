#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include "card.h"

class Enchantment : public Card{
public:
	Enchantment(std::string name,std::string type,std::string detail,
				 int magicCost, int targetNumEff);
	~Enchantment();
};

#endif
