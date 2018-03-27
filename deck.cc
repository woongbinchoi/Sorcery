#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "enchantment.h"
#include "deck.h"
#include "cardfactory.h"
#include "card.h"
#include "state.h"
using namespace std;


typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);
extern CardFactory cardFactory;

void Deck::init(string file) {
	ifstream fs{file};
	if (!fs) {
		throw Exception("File not found! Deck cannot be made");
	} else {
		string newCardString;
		while (getline(fs, newCardString)) {
			if (newCardString.empty()) continue;
			newCard nc = cardFactory.getfactory()[newCardString];
			unique_ptr<Card> c = (cardFactory.*nc)();
			deck.emplace_back(std::move(c));
		}
	}
}

void Deck::shuffle() {
	int sizeofDeck = deck.size();
	srand(time(nullptr));

	for (vector<unique_ptr<Card>>::iterator it = deck.begin(); it != deck.end(); ++it) {
		int RandNum = rand()%sizeofDeck;
		std::swap(*it, deck.at(RandNum));
	}
}

unique_ptr<Card> Deck::draw() { // card is drawn from the deck, and unique pointer of card is returned
	if(deck.size() < 1) {
		throw Exception("No more cards to draw");
	} else {
		unique_ptr<Card> drawnCard = std::move(deck.back()); // from the deck, card object is moved from the vector 
		deck.pop_back(); // we have to do this to decrease the size of vector
		return std::move(drawnCard); // we return drawncard so we can use the drawn card as unique_ptr<Card> newCard = deck.draw(); or something
	}
}
void Deck::assignOwner(int p){
	if (p == 1){
		for(auto&n : deck){
			n->getStatus().owner = CardType::Player1;
			n->whoOwner() = CardType::Player1;
		}
	}	
	else if (p == 2){
		for (auto&n : deck){
			n->getStatus().owner = CardType::Player2;
			n->whoOwner() = CardType::Player2;
		}
	}
}
