#ifndef SG_WEAPON_BASE_H
#define SG_WEAPON_BASE_H

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "SGObserver.h"
#include <vector>
#include "SGSObj.h"

NS_CC_BEGIN

typedef enum {
	WEAPON_ATTACK = 0,
	WEAPON_DEFENSE,
	WEAPON_ASSIST
} WEAPON_ATTR;

typedef enum {
	WEAPON_COMMON = 0,
	WEAPON_SUPER,
} WEAPON_TYPE;

typedef struct {
	int attack;
	int defense;
	int spirit;
	int morale;
	int explosive;
	int move;
	int hpPercent;
	int hp;
	int mp;
} Weapon_Plus;

typedef struct {
	std::string code_name;
	std::string display_name;
	std::string category;
	std::string effect;
	std::string description;
	WEAPON_ATTR attribute;
	WEAPON_TYPE type;
	int corps_avail_1;
	int corps_avail_2;
	int corps_avail_3;
	int corps_avail_4;	
	SpriteFrame* frame;
	std::vector<int> attack;
	std::vector<int> defense;
	std::vector<int> spirit;
	std::vector<int> morale;
	std::vector<int> explosive;
	std::vector<int> move;
	std::vector<int> hpPercent;
	std::vector<int> hp;
	std::vector<int> mp;
	std::vector<int> growth_curve;
} Weapon_Full_Info;

class SGWeaponBase : public Sprite {
public:
	explicit SGWeaponBase(int level = 0) { __level = level;}
	static SGWeaponBase* Create(const char* weapon_name, int level = 0);
	bool init(const char* weapon_name);
	int loadWeaponParamsFromRepo();
	std::string getDisplayName() { return __pInfo->display_name; }
	std::string getCodeName() { return __pInfo->code_name; }
	std::string getCategory() { return __pInfo->category; }
	std::string getDescription() { return __pInfo->description; }
	//std::string getEffect();		//TODO: Sometimes this has to be customized according to the plus value.
	WEAPON_ATTR getAttribute() { return __pInfo->attribute; }
	WEAPON_TYPE getType() { return __pInfo->type; }
	int getLevel() { return __level; }
	int getExp() { return __exp; }
	void getCurrentWeaponPlus(Weapon_Plus *pPlus);
	void incExp(int value);

private:
	Weapon_Full_Info *__pInfo;
	std::string __name;
	unsigned int __exp;
	unsigned int __level;
};

NS_CC_END
	
#endif
