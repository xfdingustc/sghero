#ifndef SG_SKIRMISH_STRATEGY_STAY_H
#define SG_SKIRMISH_STRATEGY_STAY_H

#include "SGSkirmishStrategy.h"

class SGSkirmishStrategyStay : public SGSkirmishStrategy
{
public:
  void oneMove(SGSkirmishHero* hero);

};

#endif