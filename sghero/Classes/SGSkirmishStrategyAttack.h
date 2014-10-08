#ifndef SG_SKIRMISH_STRATEGY_ATTACK_H
#define SG_SKIRMISH_STRATEGY_ATTACK_H

#include "SGSkirmishStrategy.h"

class SGSkirmishStrategyAttack : public SGSkirmishStrategy
{
public:
  SGSkirmishStrategyAttack(SGSTerrain* terrain) : SGSkirmishStrategy(terrain) {}
  void oneMove(SGSHero* hero);
private:
  SGSHeroList* findAssaultableEnemyHeroes(SGSHero* hero);
  SGSHero*     getBestAssaultHero(SGSHero* hero);
};

#endif