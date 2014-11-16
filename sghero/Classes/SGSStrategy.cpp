#include "SGSStrategy.h"
#include "SGSStrategyAttack.h"
#include "SGSStrategyStay.h"
NS_CC_BEGIN
SGSStrategy::SGSStrategy(SGSTerrain* terrain) 
  : __terrain(terrain)
{
}


SGSStrategy* SGSStrategy::createStrategy(SGSHero::HERO_AI ai, SGSTerrain* terrain)
{
  SGSStrategy* strategy;
  switch (ai)
  {
  case SGSHero::HERO_AI_ATTACK:
    strategy = new SGSStrategyStay(terrain);
    break;
  case SGSHero::HERO_AI_STAY:
    strategy = new SGSStrategyStay(terrain);
    break;
  default:
    strategy = new SGSStrategyStay(terrain);
    break;
  }
  return strategy;
}
NS_CC_END