#include "SGWeaponBase.h"
#include "SGWeaponRepo.h"
#include "SGGlobalSettings.h"

USING_NS_CC;

SGWeaponBase* SGWeaponBase::Create(const char* weapon_name, int level) {
	SGWeaponBase* weapon = new SGWeaponBase(level);

	if(weapon && weapon->init(weapon_name)) {
		weapon->autorelease();
		return weapon;
	} else {
		delete weapon;
		weapon = NULL;
		return NULL;
	}
}

bool SGWeaponBase::init(const char* weapon_name) {
	if(!Sprite::init()) {
		return false;
	}

	__info.name = weapon_name;
	__exp = 0;
	loadWeaponParamsFromRepo();

	return true;
}

int SGWeaponBase::loadWeaponParamsFromRepo() {
	SGWeaponRepo *pRepo = SGWeaponRepo::instance();
	Weapon_Full_Info *pWeaponItemFull = NULL;

	if(NULL == pRepo) {
		log("Fail to update the weapon params: null repo!");
		return -1;
	}

	pWeaponItemFull = pRepo->loadWeaponItemInfo(__info.name);
	__info = *pWeaponItemFull;

	return 0;
}

void SGWeaponBase::getCurrentWeaponPlus(Weapon_Plus *pPlus) {
	pPlus->attack = __info.attack.at(__level);
	pPlus->defense = __info.defense.at(__level);
	pPlus->spirit = __info.spirit.at(__level);
	pPlus->morale = __info.morale.at(__level);
	pPlus->explosive = __info.explosive.at(__level);
	pPlus->move = __info.move.at(__level);
	pPlus->hpPercent = __info.hpPercent.at(__level);
	pPlus->hp = __info.hp.at(__level);
	pPlus->mp = __info.mp.at(__level);

	return;
}

void SGWeaponBase::incExp(int value) {
	int topLevel = 0;
	unsigned int levelExpMax = 0;

	if(__info.type == WEAPON_COMMON) {
		topLevel = 3;
		levelExpMax = common_growth_curve[__level];
	} else if(__info.type = WEAPON_SUPER) {
		topLevel = 9;
		levelExpMax = super_growth_curve[__level];
	}

	if(__level == topLevel && __exp == levelExpMax) {
		log("Weapon %s has reached the level's up limit!", __info.name.c_str());
		return;
	}
	__exp += value;
	if(__exp > levelExpMax) {
		if(__level < topLevel - 1) {
			__level++;
			__exp -= levelExpMax;
		} else {
			__exp = levelExpMax;
		}
	}
	return;
}