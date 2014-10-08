#include "SGSkirmishStrategy.h"
#include "SGSkirmishStrategyAttack.h"
#include "SGSkirmishStrategyStay.h"

SGSkirmishStrategy* SGSkirmishStrategy::createStrategy(SGSHero::HERO_AI ai, SGSTerrain* terrain)
{
  SGSkirmishStrategy* strategy;
  switch (ai)
  {
  case SGSHero::HERO_AI_ATTACK:
    strategy = new SGSkirmishStrategyAttack(terrain);
    break;
  case SGSHero::HERO_AI_STAY:
    strategy = new SGSkirmishStrategyStay(terrain);
  default:
    strategy = new SGSkirmishStrategyStay(terrain);
    break;
  }
  return strategy;
}
