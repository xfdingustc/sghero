#ifndef SG_SKIRMISH_STRATEGY_STAY_H
#define SG_SKIRMISH_STRATEGY_STAY_H

#include "SGSStrategy.h"

NS_CC_BEGIN

class SGSStrategyStay : public SGSStrategy 
{
public:
  SGSStrategyStay(SGSTerrain* terrain) : SGSStrategy(terrain) {}
  bool oneMove(SGSHero* hero);

};
NS_CC_END
#endif