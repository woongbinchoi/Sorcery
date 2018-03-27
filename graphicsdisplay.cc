#include "graphicsdisplay.h"
#include "card.h"
#include "board.h"
#include "enchantlist.h"
#include "ascii_graphics.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(int winSize):
width{winSize * 2}, height{winSize}, xw{winSize * 2, winSize} {
	CardHeight = CARD_TEMPLATE_EMPTY.size();
	CardWidth = CARD_TEMPLATE_EMPTY.at(0).length();

	xtileSize = 6;
	tileSize = 10;
	xIndent = 250;
	yIndent = 100;

	xIndentPlayer1 = (xIndent - CardWidth * xtileSize) / 2; 
	xIndentPlayer2 = xIndentPlayer1 + xIndent + (CardWidth * 5 + 2) * xtileSize;

	int Middle = 250 + xtileSize * (CardWidth * 2 + CardWidth / 2 + 2);
	int yScreen = winSize;

	xw.fillRectangle(0,0,Middle,yScreen,Xwindow::Blue);
	xw.fillRectangle(Middle,0,Middle * 2,yScreen,Xwindow::Red);
	xw.fillRectangle(xIndentPlayer1 - xtileSize, yIndent - tileSize * 4,xtileSize * (CardWidth * 5) + xIndent * 2, tileSize * (CardHeight * 5 + 15),Xwindow::White);

	int Player1x = xIndentPlayer1 + tileSize * 2;
	int Player2x = xIndentPlayer2 - tileSize * CardWidth / 2 - 30;
	int Playery = CardHeight * 5 * tileSize + yIndent * 2 - 30;
	xw.drawBigString(Player1x, Playery, "Player 1", Xwindow::Blue);
	xw.drawBigString(Player2x, Playery, "Player 2", Xwindow::Red);

	string HorizontalLine = CENTRE_GRAPHIC.at(0);
	string UpperHorizontalLine = HorizontalLine;
	string LowerHorizontalLine = HorizontalLine;
	int lastElem = HorizontalLine.length() - 1;
	UpperHorizontalLine.at(0) = EXTERNAL_BORDER_CHAR_TOP_LEFT.at(0);
	LowerHorizontalLine.at(0) = EXTERNAL_BORDER_CHAR_BOTTOM_LEFT.at(0);
	UpperHorizontalLine.at(lastElem) = EXTERNAL_BORDER_CHAR_TOP_RIGHT.at(0);
	LowerHorizontalLine.at(lastElem) = EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT.at(0);

	xw.drawString(xIndent, yIndent, UpperHorizontalLine, Xwindow::Black);
	xw.drawString(xIndent, yIndent + tileSize * CardHeight * 5, LowerHorizontalLine, Xwindow::Black);

	string bar = EXTERNAL_BORDER_CHAR_UP_DOWN;
	string InfoStr = bar;
	string MinionStr = bar;

	vector<card_template_t> temp{5, CARD_TEMPLATE_EMPTY};
	Hand1Save = temp;
	Hand2Save = move(temp);

	vector<card_template_t> temp1{20, CARD_TEMPLATE_BORDER};
	Board = move(temp1);
	Board.at(1) = CARD_TEMPLATE_EMPTY;
	Board.at(3) = CARD_TEMPLATE_EMPTY;
	Board.at(16) = CARD_TEMPLATE_EMPTY;
	Board.at(18) = CARD_TEMPLATE_EMPTY;

	for (int i = 0; i < CardHeight; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (j % 2 == 0) InfoStr += Board.at(j).at(i);
			else InfoStr += Board.at(j).at(i);
			MinionStr += Board.at(j + 5).at(i);
		}
		InfoStr += bar;
		MinionStr += bar;
		xw.drawString(xIndent, yIndent + tileSize * (1 + i + CardHeight * 0), InfoStr, Xwindow::Blue);
		xw.drawString(xIndent, yIndent + tileSize * (1 + i + CardHeight * 1), MinionStr, Xwindow::Blue);
		if (i != 10) xw.drawString(xIndent, yIndent + tileSize * (1 + i + CardHeight * 2), CENTRE_GRAPHIC.at(i), Xwindow::Black);
		xw.drawString(xIndent, yIndent + tileSize * (i + CardHeight * 3), MinionStr, Xwindow::Red);
		xw.drawString(xIndent, yIndent + tileSize * (i + CardHeight * 4), InfoStr, Xwindow::Red);
		InfoStr = bar;
		MinionStr = bar;
	}

}

bool CardCompare(card_template_t &Orig, card_template_t &New) {
	return Orig.at(1) == New.at(1) && Orig.at(5) == New.at(5) && Orig.at(9) == New.at(9);
}


void GraphicsDisplay::notify(Subject<State, Status> &data) {
	State state = data.getState();

	Player &Player1Info = state.BoardInfo->getPlayer1();
	vector<unique_ptr<Card>>& Player1GraveYard = Player1Info.getGraveyard();
	vector<unique_ptr<Card>>& Player1Board = Player1Info.getBoardCards();
	vector<unique_ptr<Card>>& Player1Hand = Player1Info.getHand();
	unique_ptr<Card>& Player1Ritual = Player1Info.getRitualCard();

	Player &Player2Info = state.BoardInfo->getPlayer2();
	vector<unique_ptr<Card>>& Player2GraveYard = Player2Info.getGraveyard();
	vector<unique_ptr<Card>>& Player2Board = Player2Info.getBoardCards();
	vector<unique_ptr<Card>>& Player2Hand = Player2Info.getHand();
	unique_ptr<Card>& Player2Ritual = Player2Info.getRitualCard();


	//Hand

	int CurrentHand1Size = Player1Hand.size();
	int CurrentHand2Size = Player2Hand.size();

	card_template_t New1;
	card_template_t New2;
	for (int i = 0; i < 5; ++i) {
		if (CurrentHand1Size <= i) New1 = CARD_TEMPLATE_EMPTY;
		else New1 = Player1Hand.at(i)->getDisplay();
		if (CurrentHand2Size <= i) New2 = CARD_TEMPLATE_EMPTY;
		else New2 = Player2Hand.at(i)->getDisplay();

		if (!CardCompare(New1, Hand1Save.at(i))) {
			xw.fillRectangle(xIndentPlayer1,yIndent + tileSize * (i * (CardHeight + 1) - 3),CardWidth * xtileSize,CardHeight * tileSize,Xwindow::White);
			for (int j = 0; j < CardHeight; ++j) {
				int yInd = yIndent + tileSize * (j + i * (CardHeight + 1) - 2);
				xw.drawString(xIndentPlayer1,yInd,New1.at(j),Xwindow::Blue);
			}

			Hand1Save.at(i) = move(New1);
		}

		if (!CardCompare(New2, Hand2Save.at(i))) {
			xw.fillRectangle(xIndentPlayer2,yIndent + tileSize * (i * (CardHeight + 1) - 3),CardWidth * xtileSize,CardHeight * tileSize,Xwindow::White);
			for (int j = 0; j < CardHeight; ++j) {
				int yInd = yIndent + tileSize * (j + i * (CardHeight + 1) - 2);
				xw.drawString(xIndentPlayer2,yInd,New2.at(j),Xwindow::Red);
			}
			Hand2Save.at(i) = move(New2);
		}
	}

	Hand1Size = CurrentHand1Size;
	Hand2Size = CurrentHand2Size;

	//Board

	int xBoard = xIndent + xtileSize;
	int yBoard = yIndent + tileSize;
	int xCard = CardWidth * xtileSize;
	int yCard = CardHeight * tileSize;


	for (int i = 0; i < 10; ++i) {
		if (i == 0) {
			New1 = Player1Ritual->getDisplay(); // 0
			New2 = Player2Ritual->getDisplay(); // 15
		} else if (i == 2) {
			New1 = Player1Info.getDisplay(); // 2
			New2 = Player2Info.getDisplay(); // 17
		} else if (i == 4) {
			if (Player1GraveYard.size() != 0) New1 = Player1GraveYard.back()->getDisplay(); // 4
			else New1 = CARD_TEMPLATE_BORDER;
			if (Player2GraveYard.size() != 0) New2 = Player2GraveYard.back()->getDisplay(); // 19
			else New2 = CARD_TEMPLATE_BORDER;
		} else if (i > 4) {
			New1 = Player1Board.at(i - 5)->getDisplay(); // i
			New2 = Player2Board.at(i - 5)->getDisplay(); // i + 5
		} else continue;
		if (!CardCompare(Board.at(i), New1)) { // assign New1 to Board vector, and draw board if notcompare, draw whitespace before
			int newi = i % 5;
			int newj = i / 5;
			int xIndex = xBoard + newi * xCard;
			int yIndex = yBoard + newj * yCard;
			xw.fillRectangle(xIndex,yIndex - tileSize,xCard,yCard,Xwindow::White);
			for (int i = 0; i < CardHeight; ++i) {
				xw.drawString(xIndex, yIndex + tileSize * i, New1.at(i), Xwindow::Blue);
			}
		}
		Board.at(i) = move(New1);
		if (i < 5 && !CardCompare(Board.at(i + 15), New2)) { // assign New1 to Board vector, and draw board if notcompare, draw whitespace before
			int newi = i % 5;
			int newj = i / 5 + 4;
			int xIndex = xBoard + newi * xCard;
			int yIndex = yBoard + newj * yCard - tileSize;
			xw.fillRectangle(xIndex,yIndex - tileSize,xCard,yCard,Xwindow::White);
			for (int i = 0; i < CardHeight; ++i) {
				xw.drawString(xIndex, yIndex + tileSize * i, New2.at(i), Xwindow::Red);
			}
			Board.at(i + 15) = move(New2);
		} else if (i > 4 && !CardCompare(Board.at(i + 5), New2)) {
			int newi = i % 5;
			int newj = i / 5 + 2;
			int xIndex = xBoard + newi * xCard;
			int yIndex = yBoard + newj * yCard - tileSize;
			xw.fillRectangle(xIndex,yIndex - tileSize,xCard,yCard,Xwindow::White);
			for (int i = 0; i < CardHeight; ++i) {
				xw.drawString(xIndex, yIndex + tileSize * i, New2.at(i), Xwindow::Red);
			}
			Board.at(i + 5) = move(New2);
		}
	}
}
