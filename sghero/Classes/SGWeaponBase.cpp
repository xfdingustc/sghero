#include "SGWeaponBase.h"
#include "SGGlobalSettings.h"

USING_NS_CC;

SGWeaponBase* SGWeaponBase::Create(const char* weapon_name) {
	SGWeaponBase* weapon = new SGWeaponBase;

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
	//__level = 0;
	__exp = 0;
	updateWeaponParamsFromRepo(__level);

	return true;
}

int SGWeaponBase::updateWeaponParamsFromRepo(int level) {
	
	return 0;
}

void SGWeaponBase::incExp(int value) {
	int topLevel = 0;
	int levelExpMax = 0;

	if(__type == WEAPON_COMMON) {
		topLevel = 3;
		levelExpMax = common_growth_curve[__level];
	} else if(__type = WEAPON_SUPER) {
		topLevel = 9;
		levelExpMax = super_growth_curve[__level];
	}

	if(__level == topLevel && __exp == levelExpMax) {
		log("Weapon %s has reached the level's up limit!", __name.c_str());
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