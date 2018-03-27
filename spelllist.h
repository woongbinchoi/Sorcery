#ifndef SPELLLIST_H
#define SPELLLIST_H
#include "spell.h"
#include "subject.h"
class Banish : public Spell{
public:
	Banish();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void doEffect() override;
	void useCard() override;
};

class Unsummon : public Spell{
public:
	Unsummon();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void doEffect() override;
	void useCard() override;
};

class Recharge : public Spell{
public:
	Recharge();
	void doEffect(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void useCard(Card& target) override;
};

class Disenchant : public Spell{
public:
	Disenchant();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void doEffect() override;
	void useCard() override;
};

class RaiseDead : public Spell{
public:
	RaiseDead();
	void doEffect(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void useCard(Card &target) override;
};

class Blizzard : public Spell{
public:
	Blizzard();
	void doEffect(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void useCard(Card &target) override;
};

// other cards
class Refresh : public Spell{
public:
	Refresh();
	void doEffect(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void useCard(Card &target) override;
};
#endif
