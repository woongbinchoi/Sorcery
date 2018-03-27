#include "board.h"
#include "subject.h"
#include "observer.h"
#include "textdisplay.h"
#include "graphicsdisplay.h" // 5
#include "cardfactory.h"
#include "emptycard.h"
#include <memory>

using namespace std;

extern CardFactory cardFactory;
typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);

void Board::init(string deck1, string deck2, string player1, string player2) {	

	this->deck1->init(deck1);
	this->deck2->init(deck2);
	this->deck1->assignOwner(1);
	this->deck2->assignOwner(2);
	//shuffle the deck

	if (!testing){
		this->deck1->shuffle();
		this->deck2->shuffle();
		this->deck2->shuffle();
	}

	p1 = move(std::make_unique<Player>(player1, "player", CardType::Player1, ""));
	p2 = move(std::make_unique<Player>(player2, "player", CardType::Player2, ""));

	//initialize players by drawing 5 cards
	this->p1->init(this);
	playerTurn = 2;
	this->p2->init(this);
	playerTurn = 1;
	td = move(make_unique<TextDisplay>());
	if (graphics){
		gd = move(make_unique<GraphicsDisplay>(800)); // 3
	}
	else{
		gd = nullptr;
	}
	setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->notify(*this);
	if (gd) gd->notify(*this); // 4

	td->printBoard();
	toggleInit();
}


void Board::cleanBoard() {
	Player &active = activePlayer();
	Player &inactive = nonactivePlayer();

	std::vector<std::unique_ptr<Card>>& activeboard = active.getBoardCards();
	std::vector<std::unique_ptr<Card>>& inactiveboard = inactive.getBoardCards();

	for (int i = 0; i < 5; i++) {
		if (activeboard[i]->getStatus().hp <= 0)
			removeCard(*activeboard[i]);
	}

	std::unique_ptr<Card> &ritualcard = active.getRitualCard();

	if (ritualcard->getStatus().hp <= 0) {
		std::unique_ptr<Card> emptycard = std::make_unique<EmptyCard>();
		active.setRitualCard(std::move(emptycard));
	}
	for (int i = 0; i < 5; i++) {
		if (inactiveboard[i]->getStatus().hp <= 0)
			removeCard(*inactiveboard[i]);
	}
	std::unique_ptr<Card> &ritualcard2 = inactive.getRitualCard();
	if (ritualcard2->getStatus().hp <= 0) {
		std::unique_ptr<Card> emptycard = std::make_unique<EmptyCard>();
		inactive.setRitualCard(std::move(emptycard));
	}
	//setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->notify(*this);
	if (gd) gd->notify(*this); // 4

}

void Board::playCard(std::unique_ptr<Card> card) {
		// very similar to playACard.
	// figure out who's current turn it is and play the card c onto ther current player's turn
	// to do this, make a new card c and then move it to the current players board field (DO NOT WORRY ABOUT CHECKING TO SEE IF THERES ENOUGH SPACE, THE EFFECTS TAKE CARE OF THAT)
	// tell the board to notify everyone that a card was played by changing the state of the board

	Player &active = activePlayer();
	std::vector<std::unique_ptr<Card>>& boardCards = active.getBoardCards();
	for (int i = 0; i < 5; i++) {
		if (boardCards[i]->getType() == "") {
			boardCards[i] = std::move(card);

			//change the status of the board for the position the card that got played.
			getStatus().pos = i;
			// change the status of the card to be the position on the board.
			boardCards[i]->getStatus().pos = i;
			break;
		}
	}

}

void Board::playACard(int i, int p, int j) {
	Player &activeplayer = activePlayer();
	//call player's play a card to play a card from the player's hand

	string cardtype = activeplayer.getHand()[i]->getType();
	activeplayer.playACard(i, p, j);

	setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->notify(*this);
	if (gd) gd->notify(*this); // 4

	CardType typeplaced;
	if (cardtype == "Minion") {
		typeplaced = CardType::Minion;
	
		setState({StateType::Played, typeplaced, activeplayer.whichPlayer(), nullptr  ,this});
	} else if (cardtype == "Ritual") {
		typeplaced = CardType::Ritual;
		setState({StateType::Played, typeplaced, activeplayer.whichPlayer(), nullptr  ,this});
	}

	boardNotifyAll();

	if (showBoardAfterPlay) td->printBoard();
	if (showHandAfterPlay){
		activePlayer().whichPlayer() == CardType::Player1 ? td->printHand(1) : td->printHand(2);
	}
} 

void Board::discard(int i) {

	//discard the card
	Player &active = activePlayer();	
	std::vector<std::unique_ptr<Card>>& hand = active.getHand();
	hand.erase(hand.begin() + (i -1));
	setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->notify(*this);
	if (gd) gd->notify(*this); // 4
	if (showBoardAfterPlay) td->printBoard();
	if (showHandAfterPlay){
		activePlayer().whichPlayer() == CardType::Player1 ? td->printHand(1) : td->printHand(2);
	}
}

void Board::useACard(int i, int p, int j) {
    Player &activeplayer = activePlayer();
    try {
		activeplayer.useACard(i, p, j);
	} catch (const Exception & e) {
		throw;
	}
	if (showBoardAfterPlay) td->printBoard();
	if (showHandAfterPlay){
		activePlayer().whichPlayer() == CardType::Player1 ? td->printHand(1) : td->printHand(2);
	}
}

void Board::attackCard(int i, int j) {
	//SETSTATE
	if (j == -1) {

		Card &target = nonactivePlayer();

		Player &activeplayer = activePlayer();
		std::vector<std::unique_ptr<Card>>& activeboard = activeplayer.getBoardCards();
		Card &myminion = *(activeboard[i]);

		myminion.useCard(target);

	}
	else{
		Player &active = activePlayer();
		Player &targetplayer = nonactivePlayer();

		std::vector<std::unique_ptr<Card>>& activeboard = active.getBoardCards();
		std::vector<std::unique_ptr<Card>>& targetboard = targetplayer.getBoardCards();

		Card &myminion = *(activeboard[i]);
		Card &targetminion = *(targetboard[j]);
		myminion.useCard(targetminion);
	}
	setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->notify(*this);

}

void Board::removeCard(Card& c) {
	// if the card was a ritual just get rid of it



	// if the card was a minion, get it's name and make a new minion of the same type
	// before you get rid of the dead minion save it's status with Status s = getStatus() or whatever
	// then go give the new minion the dead minions status.
	// pass that dead minion to TextDisplay
	// Textdisplay will read it's status (status has pos of where that card was) and update the board accordingly
	// then put the new dead minion you just made into the graveyard
	// get rid of the old dead miniondl;
	string cardtype = c.getType();
	Player &activeplayer = activePlayer();

	if (cardtype == "Minion") {
			//SETSTATE
		setState({StateType::Remove, CardType::Minion, activeplayer.whichPlayer(), nullptr, this});
		boardNotifyAll();

		newCard nc = cardFactory.getfactory()[c.getName()];
		std::unique_ptr<Card> originalcard = (cardFactory.*nc)();
		int cardpos = c.getStatus().pos; 


		Player &player1 = getPlayer1();
		Player &player2 = getPlayer2();

		std::vector<std::unique_ptr<Card>> &player1board = player1.getBoardCards();
		std::vector<std::unique_ptr<Card>> &player2board = player2.getBoardCards();


		if ( (&(*player1board[cardpos])) == &c) {
			std::unique_ptr<Card> emptycard = std::make_unique<EmptyCard>();
			player1board[cardpos] = std::move(emptycard);
		}

		if ( &(*(player2board[cardpos])) == &c) {
			std::unique_ptr<Card> emptycard = std::make_unique<EmptyCard>();
			player2board[cardpos] = std::move(emptycard);
		}

		CardType owner = c.getStatus().owner;


		if (owner == CardType::Player1) {
			player1.getGraveyard().emplace_back(std::move(originalcard));
			--player1.getMinionsOnField();
		} else if (owner == CardType::Player2) {
			player2.getGraveyard().emplace_back(std::move(originalcard));
			--player2.getMinionsOnField();
		}
	} 


}

void Board::returnCard(Card& c) {
	// figure out if the card belongs in player1's hand or player's2 hand.
		// you look at the card c's status, it'll have the location in there
		// check player1's board and see if the addresses match at that location
		// if it does, then it's their card, and then make a new card and give it to them in player1's hand
		// then you need to call removeCard on that card
		// if it doesn't match, then you know it's player's 2 board 


		//SETSTATE

	Player &activeplayer = activePlayer();
	setState({StateType::Remove, CardType::Minion, activeplayer.whichPlayer(), nullptr, this});
	boardNotifyAll();
	Player &player1 = getPlayer1();
	Player &player2 = getPlayer2();

	int cardpos = c.getStatus().pos; 

	std::vector<std::unique_ptr<Card>> &player1board = player1.getBoardCards();
	std::vector<std::unique_ptr<Card>> &player2board = player2.getBoardCards();

	newCard nc = cardFactory.getfactory()[c.getName()];
	std::unique_ptr<Card> originalcard = (cardFactory.*nc)();

	if ((&(*player1board[cardpos])) == &c) {
		//if the returned card is player1's card, then make original card and put it to the player's hand
		//make the empty card on teh board
		std::unique_ptr<Card> emptycard = std::make_unique<EmptyCard>();
		player1board[cardpos] = std::move(emptycard);
		player1.getHand().emplace_back(move(originalcard));
		--player1.getMinionsOnField();
	}

	if (&(*(player2board[cardpos])) == &c) {
		std::unique_ptr<Card> emptycard = std::make_unique<EmptyCard>();
		player2board[cardpos] = std::move(emptycard);
		player2.getHand().emplace_back(move(originalcard));
		--player2.getMinionsOnField();
	}

}
void Board::toggleGraphics(){
	graphics = !graphics;
}

void Board::toggleTesting(){
	testing = !testing;
}
void Board::toggleShowBoard(){
	showBoardAfterPlay = !showBoardAfterPlay;
}
void Board::toggleShowHand(){
	showHandAfterPlay = !showHandAfterPlay;
}
void Board::toggleInit(){
	initing = !initing;
}
Player& Board::activePlayer() {
	// check who's turn it is first
	if (playerTurn == 1)
		return *p1; 
	else 
		return *p2;
}

Player& Board::nonactivePlayer() {
	// check who's turn it is first
	if (playerTurn == 1)
		return *p2; 
	else 
		return *p1;
}

void Board::changePlayerTurn() {
	playerTurn = (playerTurn + 1) % 2;

	if (playerTurn == 1){
		setState({StateType::Start,CardType::None, CardType::Player1,nullptr,this});
		boardNotifyAll();
	}
	else{
		setState({StateType::Start,CardType::None, CardType::Player2,nullptr,this});
		boardNotifyAll();
	}
}

Player& Board::getPlayer1() {
	return *p1;
}

Player& Board::getPlayer2() {
	return *p2;
}

unique_ptr<Deck> &Board::activePlayerDeck() {
	if (activePlayer().whichPlayer() == getPlayer1().whichPlayer()) return deck1;
	else return deck2;
}

void Board::playerDraw() {

	if (!activePlayer().isHandFull()) {
		activePlayer().getHand().emplace_back(activePlayerDeck()->draw());
		activePlayer().getHand().back()->setToBoard(this); 

		 // draw() returns a move constructed unique_ptr object. 
	} else {
		throw Exception{"Player's hand is full."};
	}
	if (!initing) {
		setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
		td->notify(*this);
		if (gd) gd->notify(*this); // 4
	}
	if (showBoardAfterPlay && testing) td->printBoard();
	if (showHandAfterPlay && testing){
		activePlayer().whichPlayer() == CardType::Player1 ? td->printHand(1) : td->printHand(2);
	}

}


void Board::boardNotifyAll() {

	Player &active = activePlayer();
	Player &inactive = nonactivePlayer();


	std::vector<std::unique_ptr<Card>>& activeboard = active.getBoardCards();
	std::vector<std::unique_ptr<Card>>& inactiveboard = inactive.getBoardCards();


	for (auto& card: activeboard){
		card->notify(*this);
		card->notifyAllEnchant();
	};

	std::unique_ptr<Card> &ritualcard = active.getRitualCard();
	ritualcard->notify(*this);

	
	for (auto& card: inactiveboard) {
		card->notify(*this);
		card->notifyAllEnchant();
	}
	std::unique_ptr<Card> &ritualcard2 = inactive.getRitualCard();
	ritualcard2->notify(*this);
}

void Board::showCard(Card &c){
	setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->printCard(c);
}
void Board::showBoard(){
	//DISABLED FOR TRACING RIGHT NOW
	setState({StateType::Display,CardType::None,CardType::None,nullptr,this});
	td->printBoard();

}
void Board::showHand(){
	// DISABLED FOR TRACING RIGHT NOW
	if (testing) {
		td->printHand(1);
		td->printHand(2);
	} else {
		activePlayer().whichPlayer() == CardType::Player1 ? td->printHand(1) : td->printHand(2);
	}
}


//////
// void Board::update(){
// 	gd->update();
// }
void Board::actionUp(){
	for(int i = 0; i < 5; ++i){
		if (activePlayer().getBoardCards()[i]->getType() != "" &&
			activePlayer().getBoardCards()[i]->getStatus().action == 0 ){
			activePlayer().getBoardCards()[i]->getStatus().action = 1;
		}
	}	

}

void Board::end() {
	//switch board's turn

	// NEED TO CHANGE THE STATE OF THE BOARD
	cleanBoard();
	setState({StateType::End, CardType::None, activePlayer().whichPlayer(), nullptr, this});
	boardNotifyAll();


	changePlayerTurn();

	// THIS IS THE END OF THE OTHER PLAYERS TURN 
	try{
		playerDraw();
	}
	catch(...){
	}
	++activePlayer().getStatus().magic;
	actionUp();
	cleanBoard();
}

