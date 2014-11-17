#include "SGWeaponBase.h"
#include "SGWeaponRepo.h"
#include "SGGlobalSettings.h"

NS_CC_BEGIN

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

	__name = weapon_name;
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

	__pInfo = pRepo->loadWeaponItemInfo(__name);

	return 0;
}

void SGWeaponBase::getCurrentWeaponPlus(Weapon_Plus *pPlus) {
	pPlus->attack = __pInfo->attack.at(__level);
	pPlus->defense = __pInfo->defense.at(__level);
	pPlus->spirit = __pInfo->spirit.at(__level);
	pPlus->morale = __pInfo->morale.at(__level);
	pPlus->explosive = __pInfo->explosive.at(__level);
	pPlus->move = __pInfo->move.at(__level);
	pPlus->hpPercent = __pInfo->hpPercent.at(__level);
	pPlus->hp = __pInfo->hp.at(__level);
	pPlus->mp = __pInfo->mp.at(__level);

	return;
}

void SGWeaponBase::incExp(int value) {
	int topLevel = 0;
	int levelExpMax = 0;

	if(__pInfo->type == WEAPON_COMMON) {
		topLevel = 3;
	} else if(__pInfo->type = WEAPON_SUPER) {
		topLevel = 9;
	}
	
	levelExpMax = __pInfo->growth_curve.at(__level);
	
	if(__level == topLevel && __exp == levelExpMax) {
		log("Weapon %s has reached the level's up limit!", __pInfo->code_name.c_str());
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

NS_CC_END