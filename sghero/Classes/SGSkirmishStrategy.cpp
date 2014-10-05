#include "SGSkirmishStrategy.h"
#include "SGSkirmishStrategyAttack.h"
#include "SGSkirmishStrategyStay.h"

SGSkirmishStrategy* SGSkirmishStrategy::createStrategy(SGSkirmishHero::HERO_AI ai, SGSkirmishTerrain* terrain)
{
  SGSkirmishStrategy* strategy;
  switch (ai)
  {
  case SGSkirmishHero::HERO_AI_ATTACK:
    strategy = new SGSkirmishStrategyAttack(terrain);
    break;
  case SGSkirmishHero::HERO_AI_STAY:
    strategy = new SGSkirmishStrategyStay(terrain);
  default:
    strategy = new SGSkirmishStrategyStay(terrain);
    break;
  }
  return strategy;
}
