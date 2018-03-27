#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <vector>
#include <string>

#include "observer.h"
#include "ascii_graphics.h"
#include "state.h"
#include "observer.h"
#include "minion.h"

typedef std::vector<std::string> card_template_t;

class Board;

class TextDisplay: public Observer<State, Status> {
	card_template_t horizontalLine; // this does not change
	card_template_t middle; // this does not change
	std::vector<card_template_t> Board; // Board: 01234 56789 1011121314 1516171819 
	std::vector<card_template_t> Hand1; 
	std::vector<card_template_t> Hand2;
  // 	std::vector<card_template_t> Player1Info; // First Row
 	// std::vector<card_template_t> Player1Minion; // Second Row
 	// std::vector<card_template_t> Player2Minion; // Third Row
  // 	std::vector<card_template_t> Player2Info; // Fourth Row

  	int CardWidth;
    int CardHeight;
public:
  	TextDisplay();
  	void notify(Subject<State, Status> &whoNotified) override;
  	void printBoard();
  	void printHand(int i); // 1 if player 1 else 2
  	void printCard(Card &c);
};

#endif
