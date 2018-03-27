#include "cardfactory.h"
#include "spelllist.h"
#include "minionlist.h"
#include "enchantlist.h"
#include "rituallist.h"
#include "exceptions.h"

typedef std::unique_ptr<Card> (CardFactory::*newCard)(void);

CardFactory::CardFactory(){
	factory["Air Elemental"] = &CardFactory::createAirElemental;
	factory["Earth Elemental"] = &CardFactory::createEarthElemental;
	factory["Fire Elemental"] = &CardFactory::createFireElemental;
	factory["Potion Seller"] = &CardFactory::createPotionSeller;
	factory["Novice Pyromancer"] = &CardFactory::createNovicePyromancer;
	factory["Apprentice Summoner"] = &CardFactory::createApprenticeSummoner;
	factory["Master Summoner"] = &CardFactory::createMasterSummoner;
	factory["Bone Golem"] = &CardFactory::createBoneGolem;
	factory["Banish"] = &CardFactory::createBanish;
	factory["Unsummon"] = &CardFactory::createUnsummon;
	factory["Disenchant"] = &CardFactory::createDisenchant;
	factory["Raise Dead"] = &CardFactory::createRaiseDead;
	factory["Blizzard"] = &CardFactory::createBlizzard;
	factory["Giant Strength"] = &CardFactory::createGiantStrength;
	factory["Magic Fatigue"] = &CardFactory::createMagicFatigue;
	factory["Silence"] = &CardFactory::createSilence;
	factory["Dark Ritual"] = &CardFactory::createDarkRitual;
	factory["Aura of Power"] = &CardFactory::createAuraOfPower;
	factory["Standstill"] = &CardFactory::createStandstill;
	factory["Haste"] = &CardFactory::createHaste;
	factory["Recharge"] = &CardFactory::createRecharge;
	factory["Enrage"] = &CardFactory::createEnrage;
	factory["Bounty Hunter"] = &CardFactory::createBountyHunter;
	factory["Refresh"] = &CardFactory::createRefresh;
}

std::map<std::string, newCard>& CardFactory::getfactory() { return factory; }

// All the methods to create cards are down below.
std::unique_ptr<Card> CardFactory::createBanish(){
	return std::make_unique<Banish>();
}
std::unique_ptr<Card> CardFactory::createUnsummon(){
	return std::make_unique<Unsummon>();
}
std::unique_ptr<Card> CardFactory::createRecharge(){
	return std::make_unique<Recharge>();
}
std::unique_ptr<Card> CardFactory::createDisenchant(){
	return std::make_unique<Disenchant>();
}
std::unique_ptr<Card> CardFactory::createRaiseDead(){
	return std::make_unique<RaiseDead>();
}
std::unique_ptr<Card> CardFactory::createBlizzard(){
	return std::make_unique<Blizzard>();
}
std::unique_ptr<Card> CardFactory::createAirElemental(){
	return std::make_unique<AirElemental>();
}
std::unique_ptr<Card> CardFactory::createEarthElemental(){
	return std::make_unique<EarthElemental>();
}
std::unique_ptr<Card> CardFactory::createFireElemental(){
	return std::make_unique<FireElemental>();
}
std::unique_ptr<Card> CardFactory::createBoneGolem(){
	return std::make_unique<BoneGolem>();
}
std::unique_ptr<Card> CardFactory::createPotionSeller(){
	return std::make_unique<PotionSeller>();
}
std::unique_ptr<Card> CardFactory::createNovicePyromancer(){
	return std::make_unique<NovicePyromancer>();
}
std::unique_ptr<Card> CardFactory::createApprenticeSummoner(){
	return std::make_unique<ApprenticeSummoner>();
}
std::unique_ptr<Card> CardFactory::createMasterSummoner(){
	return std::make_unique<MasterSummoner>();
}
std::unique_ptr<Card> CardFactory::createGiantStrength(){
	return std::make_unique<GiantStrength>();
}
std::unique_ptr<Card> CardFactory::createEnrage(){
	return std::make_unique<Enrage>();
}
std::unique_ptr<Card> CardFactory::createHaste(){
	return std::make_unique<Haste>();
}
std::unique_ptr<Card> CardFactory::createMagicFatigue(){
	return std::make_unique<MagicFatigue>();
}
std::unique_ptr<Card> CardFactory::createSilence(){
	return std::make_unique<Silence>();
}
std::unique_ptr<Card> CardFactory::createDarkRitual(){
	return std::make_unique<DarkRitual>();
}
std::unique_ptr<Card> CardFactory::createAuraOfPower(){
	return std::make_unique<AuraOfPower>();
}
std::unique_ptr<Card> CardFactory::createStandstill(){
	return std::make_unique<Standstill>();
}
std::unique_ptr<Card> CardFactory::createBountyHunter(){
	return std::make_unique<BountyHunter>();
}
std::unique_ptr<Card> CardFactory::createRefresh(){
	return std::make_unique<Refresh>();
}

CardFactory cardFactory{};
