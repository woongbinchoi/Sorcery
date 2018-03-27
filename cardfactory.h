#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <memory>
#include <map>
#include "card.h"

class CardFactory {
	typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);
	std::map<std::string, newCard> factory;
public:
	CardFactory();
	std::map<std::string, newCard>& getfactory();

	std::unique_ptr<Card> createBanish();
	std::unique_ptr<Card> createUnsummon();
	std::unique_ptr<Card> createDisenchant();
	std::unique_ptr<Card> createRecharge();
	std::unique_ptr<Card> createRaiseDead();
	std::unique_ptr<Card> createBlizzard();
	std::unique_ptr<Card> createAirElemental();
	std::unique_ptr<Card> createEarthElemental();
	std::unique_ptr<Card> createFireElemental();
	std::unique_ptr<Card> createBoneGolem();
	std::unique_ptr<Card> createPotionSeller();
	std::unique_ptr<Card> createNovicePyromancer();
	std::unique_ptr<Card> createApprenticeSummoner();
	std::unique_ptr<Card> createMasterSummoner();
	std::unique_ptr<Card> createGiantStrength();
	std::unique_ptr<Card> createEnrage();
	std::unique_ptr<Card> createHaste();
	std::unique_ptr<Card> createMagicFatigue();
	std::unique_ptr<Card> createSilence();
	std::unique_ptr<Card> createDarkRitual();
	std::unique_ptr<Card> createAuraOfPower();
	std::unique_ptr<Card> createStandstill();
	std::unique_ptr<Card> createBountyHunter();
	std::unique_ptr<Card> createRefresh();
};

/*
how to create a new card
newCard nc = cardFactory.getfactory()["Air Elemental"];
std::unique_ptr<Card> c = (cardFactory.*nc)();

then you'd move this pointer into a deck
*/


#endif
