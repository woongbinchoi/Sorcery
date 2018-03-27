//card.h
#ifndef CARD_H
#define CARD_H
#include <vector>
#include <string>
#include <iostream>
class Enchantment;
class Minion;
class Player;
class Spell;
class Ritual;
class Board;

#include "observer.h"
#include "subject.h"
#include "exceptions.h"
#include "state.h"
#include "status.h"
#include "ascii_graphics.h"

typedef std::vector<std::string> card_template_t;

class Card: public Observer<State, Status> , public Subject<State, Status>{
protected:
	Board *b = nullptr;
	Card *equiptocard;
private:
	std::string name,type,detail;
	int magicCost,targetNumEff;
	CardType owner;
public:
	Card(std::string name,std::string type,std::string detail, int magicCost, int targetNumEff);
	virtual ~Card()=0;
	std::string getDetail(){return detail;}
	std::string getType(){return type;}
	std::string getName(){return name;}
	int getMagic(){ return magicCost;}
	int getTargetNumEff(){ return targetNumEff; } // returns the number of targets of its effect

	CardType& whoOwner(); //returns the owner
	void setOwner(int n){}; // 1 for player 1 , 2 for player 2
							// sets owner to either CardType::Player1 or CardType::Player2
	virtual void useCard(Card &card) = 0;
	virtual void useCard() = 0;
  	//void setStatus(const Status &s);
  	//^ worry about later
  	virtual void doEffect(Card &card) = 0;
  	virtual void doEffect() = 0;
  	virtual void undoEffect(Card &card){};
	void setToBoard(Board *board){b = board;}
	virtual card_template_t getDisplay() = 0;

	void useEnchantEffect();
	void applyEnchant(Card *c);
	void removeNewestEnchant();
	void notifyAllEnchant();

	//enchantment
	void equipTo(Card *c);
	Card* equipToWho();

	/*


	
	virtual void targeted(Card &other)=0;
	virtual void useCard(Minion &target){};
	virtual void useCard(Spell &target){};
	virtual void useCard(Ritual &target){};
	virtual void useCard(Enchantment &target){};
	virtual void useCard(Player &target){};
	virtual void targetedfromEff(Card &other)=0;
	virtual void doEffect(Minion &target){};
	virtual void doEffect(Spell &target){};
	virtual void doEffect(Ritual &target){};
	virtual void doEffect(Enchantment &target){};
	virtual void doEffect(Player &target){};

	
	*/


};

#endif



