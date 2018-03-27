#ifndef DECK_H
#define DECK_H
#include <vector>
#include <memory>
#include <string>

class Card;

class Deck {
 	std::vector<std::unique_ptr<Card>> deck;
public:
 	void init(std::string file = "default.deck");
 	void shuffle();
 	std::unique_ptr<Card> draw();
 	void assignOwner(int p);
};

#endif
