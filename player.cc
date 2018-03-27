#include "player.h"
#include "emptycard.h"
#include <algorithm>
using namespace std;

//player constructor

Player::Player(string name, string type, CardType cardtype, string detail)
:Card{name,type,detail,0,0}, player{cardtype} {
		getStatus().power = 0;
		getStatus().hp = 20;
		getStatus().magic = 3;
		getStatus().action = 0;
		getStatus().silence = false;

};

void Player::playACard(int i, int playertar, int tar) {


	std::unique_ptr<Card> &card = Hand[i];
	CardType enumcardtype; 
	string cardtype = card->getType();

	//get the enumcard class : this is used to be stored for setting board.
	if (cardtype == "Minion"){
		enumcardtype = CardType::Minion;
	}
	else if (cardtype == "Spell"){
		enumcardtype = CardType::Spell;
	}
	else if (cardtype == "Ritual"){
		enumcardtype = CardType::Ritual;
	}
	else{
		enumcardtype = CardType::Enchantment;
	}



	//the card does not have a target.
	if (playertar == -1 &&  tar == -1) {
		//cards can be minions, spell, ritual
		if (enumcardtype == CardType::Minion) {

			card->getStatus().pos = i;

			std::vector<std::unique_ptr<Card>>& boardCards = getBoardCards();
			for (int i = 0; i < 5; i++) {
				if (boardCards[i]->getType() == "") {
					boardCards[i] = std::move(card);
					b->getStatus().pos = i;
					//change the status of the board for the position the card that got played.
					getStatus().pos = i;
					// change the status of the card to be the position on the board.
					boardCards[i]->getStatus().pos = i;
					break;
				}
			}


			Hand.erase(Hand.begin() + i);
			++getMinionsOnField();
		} else if (enumcardtype == CardType::Spell) {
			//use the effect of the spell here 
			card->useCard();
			Hand.erase(Hand.begin() + i);
		} else if (enumcardtype == CardType::Ritual) {
			RitualCard = std::move(card);
			Hand.erase(Hand.begin() + i);
		}

	} 
	//the card has targets, ask for more inputs
	else {
		//cards can be spell, rituals, enchantment. 
		//check the targetplayer
		Player& targetPlayer = playertar == 1? b->getPlayer1() : b->getPlayer2();
		// if the target card is ritual, do something here. 
		if (tar == 5) {
			targetPlayer.setRitualCard(move(card));
		} 
		// the target card is not a ritual
		else {		
			vector<std::unique_ptr<Card>>& targetBoard = targetPlayer.getBoardCards();
			std::unique_ptr<Card>& targetcard = targetBoard[tar];

			//we use the useCard method that takes a target as parameter
			string cardtype = card->getType();
			if (enumcardtype == CardType::Spell) {
				card->useCard(*targetcard);
				Hand.erase(Hand.begin() + i);
			} else if (enumcardtype == CardType::Enchantment) {
				card->equipTo(&(*targetcard));
				card->useCard(*targetcard);
				Hand.erase(Hand.begin() + i);
			}
		}
	}
}


card_template_t Player::getDisplay() {
	int playernum = (player == CardType::Player1) ? 1 : 2;
	return display_player_card(playernum,getName(),getStatus().hp,getStatus().magic);
}

void Player::init(Board *board) {
	//set the board on initailization;
	this->b = board;
	for (int i = 0; i < 5; i++) {
		b->playerDraw();
	}
	//testing printing out hands 
	for (auto& card: Hand) {
		string name = card->getName();
	}

	for(int i = 0 ; i < 5; ++i){
		unique_ptr<Card> empty = make_unique<EmptyCard>();
		getBoardCards().emplace_back(move(empty));
	}

	unique_ptr<Card> emptyRitual = make_unique<EmptyCard>();
	setRitualCard(move(emptyRitual));


}

void Player::useACard(int i, int playertar, int tar) {
	std::unique_ptr<Card> &card = BoardCards[i];
	int targetnum = card->getTargetNumEff();
	Player& targetPlayer = playertar == 1 ? b->getPlayer1() : b->getPlayer2();

	if (targetnum == 0) {
		// if (targetPlayer.getStatus().magic >= card.getStatus().magic){
		if (!card->getStatus().silence){
			if(card->getStatus().action == 0){
				throw Exception("Your Minion seems to be exhausted");
			}
			card->doEffect();
			card->getStatus().action -= 1;
		}
		else{ 
			throw Exception("Your minion is silenced");	
		}
	}
	else {

		//check the targetplayer
		//Player& targetPlayer = playertar == 1 ? b->getPlayer1() : b->getPlayer2();
		vector<std::unique_ptr<Card>>& targetBoard = targetPlayer.getBoardCards();
		std::unique_ptr<Card>& targetcard = targetBoard[tar];
		

		if (!card->getStatus().silence){
			if(card->getStatus().action == 0){
				throw Exception("Your Minion seems to be exhausted");
			}
			card->doEffect(*targetcard);
			card->getStatus().action -= 1;
		}
		else{ 
			throw Exception("Your minion is silenced");
			}
		}
}



void Player::notify(Subject<State, Status> &data) {}


std::vector<std::unique_ptr<Card>>& Player::getGraveyard() {
	return Graveyard;
}


std::vector<std::unique_ptr<Card>>& Player::getBoardCards() {
	return BoardCards;
}
vector<unique_ptr<Card>>& Player::getHand() {
	return Hand;
}


std::unique_ptr<Card>& Player::getRitualCard() {
	return RitualCard;
}


void Player::setRitualCard(std::unique_ptr<Card> card) {
	RitualCard = move(card);
}


bool Player::isBoardFull() {
	return minionsOnField == 5;
}

bool Player::isHandFull() {
	return getHand().size() == 5;
}

bool Player::isRitualExist() {
	return isRitual;
}

int& Player::getMinionsOnField() {
	return minionsOnField;
}

CardType Player::whichPlayer() {
	return player;
} // returns back the player field

void Player::doEffect(){}
void Player::doEffect(Card&){}
void Player::useCard(){}
void Player::useCard(Card&){}

