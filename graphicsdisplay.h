#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>
#include <vector>
#include <string>

#include "status.h"
#include "observer.h"
// #include "minion.h"
#include "window.h"

typedef std::vector<std::string> card_template_t;

class Board;
class GraphicsDisplay: public Observer<State, Status> {
	std::vector<card_template_t> Board; // Board: 01234 56789 1011121314 1516171819 
	std::vector<card_template_t> Hand1Save;
	std::vector<card_template_t> Hand2Save;
  	const int width;
  	const int height;
	int CardWidth;
    int CardHeight;
    int xtileSize;
	int tileSize;
	int xIndent;
	int yIndent;
	int Hand1Size = 0;
	int Hand2Size = 0;
	int xIndentPlayer1;
	int xIndentPlayer2;
	Xwindow xw;
public:
  	GraphicsDisplay(int winSize);
  	void notify(Subject<State, Status> &data) override;
};

#endif
