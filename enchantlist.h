#ifndef ENCHANTLIST_H
#define ENCHANTLIST_H
#include "enchantment.h"

class GiantStrength : public Enchantment{
public:
	GiantStrength();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void undoEffect(Card &card);
	card_template_t getDisplay() override;

};

class Enrage : public Enchantment{
public:
	Enrage();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void undoEffect(Card &card);
	card_template_t getDisplay() override;
};

class Haste : public Enchantment{
public:
	Haste();
	void doEffect(Card &target) override;
	void notify(Subject<State, Status> &data) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void undoEffect(Card &card);
	card_template_t getDisplay() override;
};

class MagicFatigue : public Enchantment{
public:
	MagicFatigue();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void undoEffect(Card &card);
	card_template_t getDisplay() override;
};

class Silence : public Enchantment{
public:
	Silence();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void undoEffect(Card &card);
	card_template_t getDisplay() override;
};


#endif
