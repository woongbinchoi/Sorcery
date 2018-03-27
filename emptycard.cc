#include "emptycard.h"

EmptyCard::EmptyCard(): Card{"","","",-1,-1}{};

void EmptyCard::useCard(Card &target) {
	throw Exception{"You cannot use Empty Card"};
}

void EmptyCard::doEffect(Card &target) {
	throw Exception{"You cannot do effect on Empty Card"};
}
void EmptyCard::useCard() {
	throw Exception{"You cannot do effect on Empty Card"};
}
void EmptyCard::doEffect() {
	throw Exception{"You cannot do effect on Empty Card"};
}


card_template_t EmptyCard::getDisplay() {
	return CARD_TEMPLATE_BORDER;
}
EmptyCard::~EmptyCard(){}
