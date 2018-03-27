#ifndef SPELL_H
#define SPELL_H
#include "card.h"
#include "enchantment.h"
#include "subject.h"
class Spell : public Card{
public:
	Spell(std::string name,std::string type,std::string detail, int magicCost, int targetNumEff);
	//void describe();
	~Spell();
	card_template_t getDisplay() override;
	
};

#endif
