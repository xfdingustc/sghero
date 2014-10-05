#ifndef SG_SKIRMIHSH_HERO_MOVE_STRATEGY_H
#define SG_SKIRMIHSH_HERO_MOVE_STRATEGY_H

#include "cocos2d.h"
USING_NS_CC;

#include "SGSkirmishHero.h"

class SGSkirmishStrategy 
{
public:
  static SGSkirmishStrategy* createStrategy(SGSkirmishHero::HERO_AI ai);
  virtual void oneMove(SGSkirmishHero* hero) = 0;
};

#endif