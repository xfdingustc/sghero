#ifndef SG_WEAPON_REPO_H
#define SG_WEAPON_REPO_H

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "SGObserver.h"
#include <vector>
#include "json/document.h"
#include "SGWeaponBase.h"

class SGWeaponRepo {
public:
	static SGWeaponRepo *instance();
	SGWeaponRepo();
	~SGWeaponRepo();
	bool initWeaponRepo();
	Weapon_Full_Info *loadWeaponItemInfo(std::string name);
	//Weapon_Full_Info *getWeaponItemInfoByIdx(int index);		//TODO: this API may save the time of item search

private:
	static SGWeaponRepo *__pInstance;
	void registerToWeaponRepo(Weapon_Full_Info *wp_info, const rapidjson::Value &val);
	std::vector<Weapon_Full_Info*> __all_weapons;
	rapidjson::Document text_json;
	
};
#endif