#include "textdisplay.h"
#include "card.h"
#include "board.h"
#include "enchantlist.h"

using namespace std;

TextDisplay::TextDisplay() {
	CardHeight = CARD_TEMPLATE_EMPTY.size();
	CardWidth = CARD_TEMPLATE_EMPTY.at(0).length();
	int borderlength = CardWidth * 5;
	for (int i = 0; i < borderlength; ++i) {
		horizontalLine.emplace_back(EXTERNAL_BORDER_CHAR_LEFT_RIGHT);
	}
	middle = CENTRE_GRAPHIC;
	for (int i = 0; i < 20; ++i) {
		if (i == 1 || i == 3 || i == 16 || i == 18) {
			Board.emplace_back(CARD_TEMPLATE_EMPTY);
		} else {
			Board.emplace_back(CARD_TEMPLATE_BORDER);
		}
	}

}

void TextDisplay::notify(Subject<State, Status> &whoNotified) {
	State state = whoNotified.getState();
	//if (state.type != StateType::Display) return;
	Player &Player1Info = state.BoardInfo->getPlayer1();
	Player &Player2Info = state.BoardInfo->getPlayer2();
	Hand1.clear();
	Hand2.clear();
	for (auto &card : Player1Info.getHand()) {
		Hand1.emplace_back(card->getDisplay());
	}

	for (auto &card : Player2Info.getHand()) {
		Hand2.emplace_back(card->getDisplay());
	}
	for (int i = 0; i < 10; ++i) {
		if (i == 0) {
			Board.at(i) = Player1Info.getRitualCard()->getDisplay();
			Board.at(i + 15) = Player2Info.getRitualCard()->getDisplay();
		} else if (i == 2) {
			Board.at(i) = Player1Info.getDisplay();
			Board.at(i + 15) = Player2Info.getDisplay();
		} else if (i == 4) {
			if (Player1Info.getGraveyard().size() != 0) {
				Board.at(i) = Player1Info.getGraveyard().back()->getDisplay();
			}
			if (Player2Info.getGraveyard().size() != 0) {
				Board.at(i + 15) = Player2Info.getGraveyard().back()->getDisplay();
			}
		} else if (i > 4) {
			Board.at(i) = Player1Info.getBoardCards().at(i - 5)->getDisplay();
			Board.at(i + 5) = Player2Info.getBoardCards().at(i - 5)->getDisplay();
		}
	}
}

void TextDisplay::printBoard() {
	cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
	for (auto p : horizontalLine) {
		cout << p;
	}
	cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;

	for (int i = 0; i < 4; ++i) {
		if (i == 2) {
			for (auto p : middle) {
				cout << p << endl;
			}
		}
		for (int j = 0; j < CardHeight; ++j) {
			cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
			for (int k = 0; k < 5; ++k) {
				cout << Board.at(i * 5 + k).at(j);
			}
			cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
		}
	}

	cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
	for (auto p : horizontalLine) {
		cout << p;
	}
	cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void TextDisplay::printHand(int i) {
	std::vector<card_template_t> &Hand = (i == 1) ? Hand1 : Hand2;
	int size = Hand.size();

	for (int i = 0; i < CardHeight; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << Hand.at(j).at(i);
		}
		cout << endl;
	}
}

void TextDisplay::printCard(Card &c) {
	card_template_t TargetCard = c.getDisplay();

	vector<card_template_t> EnchantStrVec;


	for (auto &p : c.getStatus().enchants) {
		EnchantStrVec.emplace_back(p->getDisplay());
	}
	int size = EnchantStrVec.size();
	for (auto p : TargetCard) {
		cout << p << endl;
	}
	int y = size / 5 + 1;
	for (int i = 0; i < CardHeight * y; ++i) {
		for (int j = 0; j < y; ++j) {
			for (int k = 0; k < 5; ++k) {
				cout << EnchantStrVec.at(j * 5 + k).at(i % CardHeight);
			}
			cout << endl;
		}
		
	}
}
