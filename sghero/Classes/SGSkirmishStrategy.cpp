#include "SGSkirmishStrategy.h"
#include "SGSkirmishStrategyStay.h"

SGSkirmishStrategy* SGSkirmishStrategy::createStrategy(SGSkirmishHero::HERO_AI ai)
{
  SGSkirmishStrategy* strategy = new SGSkirmishStrategyStay();
  return strategy;
}
