#ifndef SG_SKIRMISH_STRATEGY_ATTACK_H
#define SG_SKIRMISH_STRATEGY_ATTACK_H

#include "SGSkirmishStrategy.h"

class SGSkirmishStrategyAttack : public SGSkirmishStrategy
{
public:
  SGSkirmishStrategyAttack(SGSkirmishTerrain* terrain) : SGSkirmishStrategy(terrain) {}
  void oneMove(SGSkirmishHero* hero);

};

#endif