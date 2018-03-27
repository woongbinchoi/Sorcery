#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"

class Ritual : public Card{
public:
	Ritual(std::string name,std::string type,std::string detail, 
		int magicCost, int targetNumEff);
	~Ritual();
	card_template_t getDisplay() override;
};

#endif
