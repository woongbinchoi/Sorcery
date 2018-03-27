#ifndef STATUS_H
#define STATUS_H

#include <memory>
#include "state.h"
class Enchantment;
struct Status {
	int pos = 0;
	int power = 0;
	int magic = 0;
	int hp = 0;
	int action = 0;
	bool silence;
	std::vector<std::unique_ptr<Card>> enchants;
	CardType owner = CardType::None;
};

#endif
