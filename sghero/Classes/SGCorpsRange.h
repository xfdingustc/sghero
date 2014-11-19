#ifndef SG_CORPS_RANGE_H
#define SG_CORPS_RANGE_H

#include "SGCorpsRepo.h"
#include "SGSPoint.h"

NS_CC_BEGIN

class SGCorpsAttackRange {
public:
	static SGCorpsAttackRange *instance();
	SGCorpsAttackRange();
	~SGCorpsAttackRange();
	bool initAttackRange();
	SGSPointList *getAttackRange(SGCorpsRepo::CORPS_ATTACK_RANGE type) { return &rangeList[static_cast<int>(type)];}
	
private:
	static SGCorpsAttackRange *__pInstance;
	SGSPointList rangeList[SGCorpsRepo::CORPS_RANGE_MAX]; 
};
NS_CC_END
#endif