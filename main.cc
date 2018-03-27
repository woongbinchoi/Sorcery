//main.cc
#include "cardfactory.h"
#include "minionlist.h"
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h" // 6
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

	string deck1name = "default.deck";
	string deck2name = "default.deck";
	string player1name = "player1";
	string player2name = "player2";
	string initfilename = "";

	//storing the help message when the user issues help command 
	ifstream fs{"help.txt"};
	if (!fs){
		cout << "could not find help file text" << endl;
	}
	bool graphics  = false;
	bool testing = false;

	for(int i = 1; i < argc; ++i){
		string s = argv[i];
		if (s == "-deck1"){
			deck1name = argv[++i];
		}
		else if (s == "-deck2"){
			deck2name = argv[++i];
		}
		else if (s == "-graphics"){
			graphics  = true;
		}
		else if (s == "-init"){
			initfilename = argv[++i];
		}
		else if (s == "-testing"){
			testing = true;
		}
		else if (s == "-graphics"){
			graphics = true;
		}
	}

	streambuf* buffer;
	ifstream initfile;
	if (initfilename != ""){
		initfile.open(initfilename);
		buffer = initfile.rdbuf();
	}
	else{
		buffer = cin.rdbuf();
	}
	istream input{buffer};


	unique_ptr<Board> board = std::make_unique<Board>();
	if (testing == true) board->toggleTesting();
	if (graphics == true) board->toggleGraphics();
	input >> player1name >> player2name;
	board->init(deck1name, deck2name, player1name, player2name);
	string s;

  try {
  	cout << player1name << "'s turn" << endl;
	while (true) {
		input >> s;
		if(input.eof()){
			input.rdbuf(cin.rdbuf());
			initfile.close();
			continue;
	    }
	    if (s == "help") {
	    	string messageline;
	    	while (getline(fs, messageline)) {
				cout << messageline << endl;
			}
	    }
	    
	    else if (s == "end") {
	   		//this is for testing the cards

	   		board->end();
			if (board->activePlayer().whichPlayer() == CardType::Player1){
				cout << player1name << "'s turn" << endl;
			}
			else{
				cout << player2name << "'s turn" << endl;
			}

	    }
	    else if (s == "quit") {
	    	break;
	    }
	    else if (s == "draw" && testing) {
	    	try{
	    		board->playerDraw();

	    	} // needs to do more than this. This draw is only available for testing mode though
	    	catch(Exception& e){
	    		cout << e.why() << endl;
	    	}
	    }

	    else if (s == "discard") {
	    	//if the testing is set to true
	    	if (testing) {
	    		int i; 
	    		input >> i;
	    		board->discard(i);
	    	}
	    }

	    else if (s == "attack") {
	    	//i couldnt think of a better method maybe change this logic
	    	string in;
	    	getline(input, in);
	    	istringstream ss{in};
	    	int n;
	    	int i = 2;
	    	int j = 2; 
	    	int counter = 0;
	    	while (ss >> n) {
	    		++counter;
	    		if (counter == 1){
	    			i = n;
	    		}
	    		else if (counter == 2){
	    			j = n;
	    		}
	    	}
	    	i -= 1;
	    	j -= 1;
	    	//check invalid inputs
	    	if (i < 0 || i >= 5 || j < 0 || j >= 5) {
	    		cout << "invalid inputs" << endl;
	    	}

	    	try {
	    		if (board->activePlayer().getBoardCards()[i]->getStatus().action > 0){
			    	if (counter == 1) {
			    		board->attackCard(i);
						--board->activePlayer().getBoardCards()[i]->getStatus().action;
			    	}
			    	else if (counter == 2) {
			    		board->attackCard(i, j);
						--board->activePlayer().getBoardCards()[i]->getStatus().action;
			    	}
			    	else {
			    		cout << "Invalid Input." << endl;
			    	}
			    }
			    else{
	    			if(board->activePlayer().getBoardCards()[i]->getType() == ""){
	    				cout << "There is no minion here" << endl;
	    			}
	    			else{
	    				cout << "The minion seems to be exhausted" << endl;
	    			}
	    		}
	    	} 
	    	catch (const std::exception& e) {
	    	}
	    	catch (...){
	    	}
	    	board->cleanBoard();

	    }

	    else if (s == "play") {
	    	string in;
	    	getline(input, in);
	    	istringstream ss{in};
	    	int n;
	    	int i = 2;
	    	int p = 0; 
	    	int t = 0;
	    	int counter = 0;
	    	while (ss >> n) {
	    		++counter;
	    		if (counter == 1){
	    			i = n;
	    		}
	    		else if (counter == 2){
	    			p = n;
	    		}
	    		else if (counter == 3){
	    			t = n;
	    		}
	    	}
	    	--i;
	    	--t;
	    	//check invalid inputs
	    	if (i < 0 || i >= 5) {
	    		cout << "Invalid inputs" << endl;
	    		continue;
	    	}
	    	unsigned int m = i+1;
	    	if (board->activePlayer().getHand().size() < m){
	    		cout << "Invalid Move" << endl;
	    	}
	    	else if (t == -1 && p == 0){
	    		try{
	    			int cost = board->activePlayer().getHand()[i]->getMagic();
	    			if (board->activePlayer().getStatus().magic >= cost) {
	    				board->playACard(i);
	    				board->activePlayer().getStatus().magic -= cost;
	    				board->cleanBoard();
	    			}
	    			else if (board->activePlayer().getStatus().magic < cost && testing){
	    				board->playACard(i);
	    				board->activePlayer().getStatus().magic = 0;
	    				board->cleanBoard();
	    			}
	    			else{
	    				cout << "Not Enough Magic." << endl;
	    			}
	    		}
	    		catch(...){
	    			cout << "Invalid Move" << endl;
	    		}
	    	}
	    	else if ((t < 5 && t >= 0 ) && (p == 1 || p == 2)){
	    		try{
	    			int cost = board->activePlayer().getHand()[i]->getMagic();
	    			if (board->activePlayer().getStatus().magic >= cost) {
	    				board->playACard(i,p,t);


	    				board->activePlayer().getStatus().magic -= cost;
	    				board->cleanBoard();
	    			}
	    			else if (board->activePlayer().getStatus().magic < cost && testing){
	    				board->playACard(i,p,t);
	    				board->activePlayer().getStatus().magic = 0;
	    				board->cleanBoard();
	    			}
	    			else {
	    				cout << "Not Enough Magic." << endl;
	    			}
	    		}
	    		catch(...){
	    			cout << "Invalid Move" << endl;
	    		}
	    	}
	    	else{
	    		cout << "Invalid Move" << endl;
	    	}
	    }

	    else if (s == "use") {
	    	string in;
	    	getline(input, in);
	    	istringstream ss{in};
	    	int n;
	    	int i = 2;
	    	int p = 0; 
	    	int t = 0;
	    	int counter = 0;
	    	while (ss >> n) {
	    		++counter;
	    		if (counter == 1){
	    			i = n;
	    		}
	    		else if (counter == 2){
	    			p = n;
	    		}
	    		else if (counter == 3){
	    			t = n;
	    		}
	    	}
	    	--i;
	    	--t;

	    	if (i < 0 || i >= 5) {
	    		cout << "Invalid inputs" << endl;
	    		continue;
	    	}

	    	if  (t == -1 && p == 0){
	    		try{
	    			int cost = board->activePlayer().getBoardCards()[i]->getStatus().magic;
	    			if (board->activePlayer().getStatus().magic >= cost){
	    				board->useACard(i);
	    				board->activePlayer().getStatus().magic -= cost;
	    				board->cleanBoard();
	    			}
	    			else if (testing){
	    				board->activePlayer().getStatus().magic = 0;
	    				board->useACard(i);
	    				board->cleanBoard();
	    			}
	    			else{
	    				cout << "Not enough magic to use this ability." << endl;
	    			}
	    		}
	    		catch( Exception &e){
				    cout << e.why() << endl;
				}
	    	}
	    	else if ((t < 5 && t >= 0) && (p == 1 || p == 2)){
		    	try{
			    	int cost = board->activePlayer().getBoardCards()[i]->getStatus().magic;
			    	if (board->activePlayer().getStatus().magic >= cost){
			    		board->useACard(i,p,t);
			    		board->activePlayer().getStatus().magic -= cost;
			    		board->cleanBoard();
			    	}
			    	else if (testing){
			    		board->activePlayer().getStatus().magic = 0;
			    		board->useACard(i,p,t);
			    		board->cleanBoard();
			    	}
			    	else{
			    		cout << "Not enough magic to use this ability." << endl;
			    	}
				}
				catch(...){
				    cout << "Invalid Move" << endl;
				}
	    	//clean the board
	 	   }
	 	   else{
	 	   	cout << "Invalid Move" << endl;
	 	   }
		}
	    else if (s == "describe") {
	    	// CHECKS OUT A MINION ON THE CURRENT PLAYER
	    	int i;
	    	input >> i;

	    	if (i >= 1 && i <= 5 && board->activePlayer().getBoardCards()[i -1]->getType() != ""){
	    		board->showCard(*board->activePlayer().getBoardCards()[i -1]);
	    	}
	    	else{
	    		cout << "Invalid target" << endl;
	    	}
	    }
	    else if (s == "hand") {
	    	// LOOP THROUGH THE CURRENT PLAYERS HAND AND LIST OUT THE CARDS
	    	board->showHand();
	    }

	    else if (s == "board") {
	    	// td->printBoard();
	    	board->showBoard();
	    }

	    //if (input.peek() == std::ifstream::traits_type::eof()){
	   // if(input.eof()){
	//		input.rdbuf(cin.rdbuf());
//			initfile.close();
//			input.sync();
//	    }

	    // check if win condition is met
	    if (board->getPlayer1().getStatus().hp <= 0 && board->getPlayer2().getStatus().hp <= 0){
	    	cout << "TIE!" << endl;
			break;
	    }
	    else if( board->getPlayer1().getStatus().hp <= 0){
	    	cout << player2name << " wins!!!" << endl;
			break;
	    }
	    else if (board->getPlayer2().getStatus().hp <= 0){
	    	cout << player1name << " wins!!!" << endl;
			break;
	    }
  	}
  }catch (Exception &e){
  	cout << e.why() << endl;	
  }catch (...){
  	cout << "Fatal error has occured, program is now terminating" << endl;
  }
	return 0;
}
