#ifndef SG_SKIRMISH_STRATEGY_STAY_H
#define SG_SKIRMISH_STRATEGY_STAY_H

#include "SGSStrategy.h"



class SGSStrategyStay : public SGSStrategy 
{
public:
  SGSStrategyStay(SGSTerrain* terrain) : SGSStrategy(terrain) {}
  bool oneMove(SGSHero* hero);

};

#endif