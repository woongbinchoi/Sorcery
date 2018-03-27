#ifndef MINION_H
#define MINION_H
#include "exceptions.h"
#include "card.h"
#include "ritual.h"
#include "enchantment.h"
#include "board.h"
#include <memory>

class Minion : public Card{
	/*int action,atk,hp,effCost;
	bool silence;*/
public:
	Minion(std::string name,std::string type,
				std::string detail,int magicCost, int targetNumEff);
	~Minion();
	virtual void useCard(Card &target) override; 
	void useCard() override;// using a minion to attack another minion
	//void remove() override;
	// void describe() override; // checks the minions enchantments
};

#endif
