#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "minion.h"
#include "state.h"
#include <memory>
class Player: public Card{
	std::vector<std::unique_ptr<Card>> Hand;
	std::vector<std::unique_ptr<Card>> BoardCards;
	std::vector<std::unique_ptr<Card>> Graveyard;
	std::unique_ptr<Card> RitualCard;
	CardType player;
	int minionsOnField = 0;
	bool isRitual = false;
public:
	Player(std::string name,std::string type, CardType cardtype, std::string detail);

	//setting the board pointer when player gets initialized
	void init(Board *b); 
	void playACard(int i, int p, int j);
	void useACard(int i, int p, int j) ;
	void notify(Subject<State, Status> &data) override;
	// //displaying
	card_template_t getDisplay() override;


	std::vector<std::unique_ptr<Card>>& getGraveyard();
	std::vector<std::unique_ptr<Card>>& getBoardCards();
	std::vector<std::unique_ptr<Card>>& getHand();
	std::unique_ptr<Card>& getRitualCard();
	int& getMinionsOnField();
	void setRitualCard(std::unique_ptr<Card> card);

	//checking if board/hand/ritual is full
	bool isBoardFull();
	bool isHandFull();
	bool isRitualExist();

	// these have no implementation
	void doEffect() override;
	void doEffect(Card&) override;
	void useCard() override;
	void useCard(Card&) override;
	/*
	int& getPlayerHealth();
	int& getPlayerMagic();
	*/
	CardType whichPlayer(); // returns back the player field
	//void describe();
};
#endif
