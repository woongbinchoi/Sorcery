#ifndef RITUALLIST_H
#define RITUALLIST_H
#include "ritual.h"
class DarkRitual : public Ritual{
public:
	DarkRitual();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void notify(Subject<State, Status> &data)override;
};

class AuraOfPower : public Ritual{
public:
	AuraOfPower();
	void doEffect(Card &target) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
	void notify(Subject<State, Status> &data) override;
};

class Standstill : public Ritual{
public:
	Standstill();
	void doEffect(Card &target) override;
	void notify(Subject<State, Status> &data) override;
	void useCard(Card &target) override;
	void useCard() override;
	void doEffect() override;
};

#endif
