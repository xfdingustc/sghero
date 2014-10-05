#ifndef SG_SKIRMISH_STRATEGY_STAY_H
#define SG_SKIRMISH_STRATEGY_STAY_H

#include "SGSkirmishStrategy.h"

class SGSkirmishStrategyStay : public SGSkirmishStrategy
{
public:
  SGSkirmishStrategyStay(SGSkirmishTerrain* terrain) : SGSkirmishStrategy(terrain) {}
  void oneMove(SGSkirmishHero* hero);

};

#endif