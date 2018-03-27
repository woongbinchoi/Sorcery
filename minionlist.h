#ifndef MINIONLIST_H
#define MINIONLIST_H
#include "minion.h"
#include "state.h"

class AirElemental: public Minion{
public:
	AirElemental();
	void doEffect() override;
	void doEffect(Card &card) override;
	card_template_t getDisplay() override;
};

class EarthElemental : public Minion{
public:
	EarthElemental();
	void doEffect() override;
	void doEffect(Card &card) override;
	card_template_t getDisplay() override;
};

class BoneGolem : public Minion{
public:
	BoneGolem();
	void doEffect() override;
	void doEffect(Card &target) override;
	void notify(Subject<State, Status> &data) override;
	card_template_t getDisplay() override;
};

// When making this card in deck.cc
// depending on who's deck we're making we have to
// change whoPlayedMe to that Player.
class FireElemental : public Minion{
public:
	FireElemental();
	void doEffect() override;
	void doEffect(Card& target) override;
	void notify(Subject<State, Status> &data) override;
	card_template_t getDisplay() override;
};

class PotionSeller : public Minion{
public:
	PotionSeller();
	void doEffect() override;
	void doEffect(Card& target) override;
	void notify(Subject<State, Status> &data) override;
	card_template_t getDisplay() override;
};

class NovicePyromancer : public Minion{
public:
	NovicePyromancer();
	void doEffect(Card& target) override;
	void doEffect() override;
	card_template_t getDisplay() override;
};

class ApprenticeSummoner : public Minion{
public:
	ApprenticeSummoner();
	void doEffect(Card& target) override;
	void doEffect() override;
	card_template_t getDisplay() override;
};

class MasterSummoner : public Minion{
public:
	MasterSummoner();
	void doEffect(Card& target) override;
	void doEffect() override;
	card_template_t getDisplay() override;
};


// other  cards

class BountyHunter : public Minion{
public:
	BountyHunter();
	void doEffect(Card& target) override;
	void doEffect() override;
	void useCard(Card& target) override;
	card_template_t getDisplay() override;
};



#endif
