#ifndef STATE_H
#define STATE_H

/* What are states and how do they work?
	What is the current state of the board.
	Played: This state means a card was just played onto the board.

	Remove: This state means that there was some card on the board that was 
			just removed from the board. 

	Start: This state means that it's the start of the turn. 

	End: This state means that it's the end of the turn.

*/
class Card;
class Board;
enum class StateType{ Played, Remove, Start, End, Display };
enum class CardType{ None, Minion, Spell, Enchantment, Ritual, Player1, Player2 };
struct State{
	StateType type;
	CardType card_t;
	CardType player;
	Card* info;
	Board *BoardInfo;
};

#endif
