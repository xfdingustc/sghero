#ifndef SG_CORPS_RANGE_H
#define SG_CORPS_RANGE_H

#include "SGCorpsRepo.h"
#include "SGSPoint.h"

NS_CC_BEGIN

class SGCorpsAttackRange {
public:
	typedef enum {
		CORPS_RANGE_HERO = 0,				// refer to qunxiong
		CORPS_RANGE_INFANTRY,				// refer to bubing
		CORPS_RANGE_MOYU,						// refer to moyujian
		CORPS_RANGE_BROAD_SWORD,		// refer to dadao
		CORPS_RANGE_BIG_MOYU,				// refer to damoyujian
		CORPS_RANGE_SUPER_BIG_MOYU,	// refer to dadamoyujian
		CORPS_RANGE_NORMAL_SWORD,		// refer to yuxia
		CORPS_RANGE_SPEAR,					// refer to baoyan
		CORPS_RANGE_LONG_SPEAR,			// refer to changbaoyan
		CORPS_RANGE_GENERAL,				// refer to hujiang
		CORPS_RANGE_HORSEARCHER,		// refer to gongbing
		CORPS_RANGE_GREAT_HORSEARCHER,	// refer to gongbing erzhuan
		CORPS_RANGE_BALLISTA,				// refer to nupao
		CORPS_RANGE_SHORTBOW,				// refer to duangong
		CORPS_RANGE_LONGBOW,				// refer to changgong
		CORPS_RANGE_STRONGBOW,			// refer to qianggong
		CORPS_RANGE_GUN_CARRIAGE,		// refer to sheri
		CORPS_RANGE_REMOTE_GUN_CARRIAGE,	// refer to yuanpao
		// TODO: Add the range of masters' strategies 
		CORPS_RANGE_MAX
	} CORPS_ATTACK_RANGE;

	static SGCorpsAttackRange *instance();
	SGCorpsAttackRange();
	~SGCorpsAttackRange();
	bool initAttackRange();
	SGSPointList *getAttackRange(SGCorpsAttackRange::CORPS_ATTACK_RANGE type) { return &rangeList[static_cast<int>(type)];}
	
private:
	static SGCorpsAttackRange *__pInstance;
	SGSPointList rangeList[SGCorpsAttackRange::CORPS_RANGE_MAX]; 
};
NS_CC_END
#endif