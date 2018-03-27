#ifndef BOARD_H
#define BOARD_H
#include "subject.h"
#include "state.h"
#include "player.h"
#include "deck.h"
#include "observer.h"
#include <memory>

class TextDisplay;
class GraphicsDisplay; //1
class Board : public Subject<State, Status>, public Observer<State, Status>{
	// The gamestate is in subject.h
	int playerTurn = 1;
	bool testing = false;
	bool showBoardAfterPlay = false;
	bool showHandAfterPlay = false;
	bool initing = true;
	bool graphics = false;
	std::unique_ptr<TextDisplay> td;
	std::unique_ptr<GraphicsDisplay> gd; //2
	std::unique_ptr<Deck> deck1 = std::make_unique<Deck>();
	std::unique_ptr<Deck> deck2 = std::make_unique<Deck>();

	std::unique_ptr<Player> p1;
	std::unique_ptr<Player> p2;

public:
	// I just made this .h so I don't forget about the state


	/* HOW THIS WORKS:
	Whenever something is done to the board, we're going to update the boards state to reflect that action
		(See subject.h gameState: Board inherates from Subject)
		Ex. When a minion is played on the board, the board can change it's state to Summoned, Minion,
			then notify all the things on the board.
			This will pass the board object to the cards, and then the cards can use getState() to check the state of the board,
			and react to the current state appropriately.*/


	/*
	// implement the other fields below
	*/
	void init(std::string deck1, std::string deck2, std::string player1 = "player 1", std::string player2 = "player 2");
	void cleanBoard();
	//everytime the player does something, at the end the board will
	// try to clean itself
	// (Board will check minions hp if <= 0 and remove them
	// and check rituals hp if <= 0 and remove them)


	// Since these are all unique vector pointers, we need to use
	// std::move + emplace_back whenever we move cards and then pop them from the vector

	//this is for creating a creating minions on the board not out of the player's hand ex. resurrect, summon
	void playCard(std::unique_ptr<Card> card);
	void attackCard(int i, int j = -1);
	//plays a card to the board
	void playACard(int i, int p = -1, int j = -1);
	void useACard(int i, int p = -1, int j = -1);
	void discard(int i);
	void toggleTesting(); // toggles testing
	void toggleShowHand(); // automatically shows hand
	void toggleShowBoard(); // automatically shows board
	void toggleInit();
	void switchTurn();
	void toggleGraphics();
	void end();
	
	void playerDraw(); // main calls this. It checks active player and give a card to the players hand if players hand is not full
	
	void removeCard(Card& c); ///does different stuff depending on the card
	void returnCard(Card& c); // makes a copy of the card from the field to the hand
	Player& activePlayer(); // returns back the current player based on the turn.
	Player& nonactivePlayer();
	void changePlayerTurn(); // change the active player's turn
	Player& getPlayer1();
	Player& getPlayer2();
	std::unique_ptr<Deck> &activePlayerDeck();

	void showCard(Card &c);
	void showHand();
	void showBoard();
	void actionUp();
	void boardNotifyAll();

};

#endif
