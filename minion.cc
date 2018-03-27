#include "minion.h"

using namespace std;

Minion::Minion(std::string name,std::string type,
				std::string detail,int magicCost, int targetNumEff):
				Card{name,type,detail,magicCost,targetNumEff}{}

void Minion::useCard(Card &target){
	//damage calculation
	target.getStatus().hp -= getStatus().power;
	getStatus().hp -= target.getStatus().power;
}

Minion::~Minion() {}

void Minion::useCard(){
	
}
