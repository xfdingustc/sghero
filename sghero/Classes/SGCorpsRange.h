#ifndef SG_CORPS_RANGE_H
#define SG_CORPS_RANGE_H

#include "SGCorpsType.h"
#include "SGSPoint.h"

class SGCorpsAttackRange {
public:
	static SGCorpsAttackRange *instance();
	SGCorpsAttackRange();
	~SGCorpsAttackRange();
	bool initAttackRange();
	SGSPointList *getAttackRange(CORPS_ATTACK_RANGE type) { return &rangeList[static_cast<int>(type)];}
	
private:
	static SGCorpsAttackRange *__pInstance;
	SGSPointList rangeList[CORPS_RANGE_MAX]; 
};
#endif