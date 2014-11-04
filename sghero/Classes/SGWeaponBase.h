#ifndef SG_WEAPON_BASE_H
#define SG_WEAPON_BASE_H

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "SGObserver.h"
#include <vector>

USING_NS_CC;

typedef enum {
	WEAPON_ATTACK = 0,
	WEAPON_DEFENSE,
	WEAPON_SPECIAL
} WEAPON_ATTR;

typedef enum {
	WEAPON_COMMON = 0,
	WEAPON_SUPER,
} WEAPON_TYPE;

typedef struct {
	int	attack;
	int	defense;
	int	spirit;
	int	morale;
	int	explosive;
	int	move;
	int hpPercent;
	int	hp;
	int	mp;
} WEAPON_PLUS;

static int common_growth_curve[3] = {150, 150, 150};
static int super_growth_curve[9] = {150, 150, 150, 200, 200, 200, 250, 250, 250};

class SGWeaponBase : public Sprite {
public:
	explicit SGWeaponBase(int level = 0) { __level = level;}
	static SGWeaponBase* Create(const char* weapon_name);
	bool init(const char* weapon_name);
	int updateWeaponParamsFromRepo(int level);
	WEAPON_ATTR getAttribute() { return __attribute; }
	WEAPON_PLUS* getPlus()	{ return __plus_table.at(__level);}
	void incExp(int value);

private:
	std::string		__name;
	std::string		__effect;
	std::string		__description;
	std::string		__class;
	unsigned int	__level;
	unsigned int	__exp;
	WEAPON_TYPE		__type;
	WEAPON_ATTR		__attribute;
	std::vector<WEAPON_PLUS *>	__plus_table;
};

#endif