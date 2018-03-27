#ifndef EMPTYCARD_H
#define EMPTYCARD_H
#include "card.h"

class EmptyCard : public Card{
public:
	EmptyCard();
	void useCard(Card &target) override;
	void doEffect(Card &target) override;
	void useCard() override;
	void doEffect() override;
	card_template_t getDisplay() override;
	~EmptyCard();
};
#endif
