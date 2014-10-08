#ifndef SG_SKIRMISH_STRATEGY_STAY_H
#define SG_SKIRMISH_STRATEGY_STAY_H

#include "SGSkirmishStrategy.h"

class SGSkirmishStrategyStay : public SGSkirmishStrategy
{
public:
  SGSkirmishStrategyStay(SGSTerrain* terrain) : SGSkirmishStrategy(terrain) {}
  void oneMove(SGSHero* hero);

};

#endif