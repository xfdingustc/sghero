#ifndef SG_SKIRMISH_STRATEGY_STAY_H
#define SG_SKIRMISH_STRATEGY_STAY_H

#include "SGSStrategy.h"

class SGSStrategyStay : public SGSStrategy
{
public:
  SGSStrategyStay(SGSTerrain* terrain) : SGSStrategy(terrain) {}
  void oneMove(SGSHero* hero);

};

#endif