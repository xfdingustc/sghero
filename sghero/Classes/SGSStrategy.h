#ifndef SG_SKIRMIHSH_HERO_MOVE_STRATEGY_H
#define SG_SKIRMIHSH_HERO_MOVE_STRATEGY_H

#include "cocos2d.h"
USING_NS_CC;

#include "SGSHero.h"
#include "SGSTerrain.h"

class SGSStrategy 
{
public:
  static SGSStrategy* createStrategy(SGSHero::HERO_AI ai, SGSTerrain* terrain);
  SGSStrategy(SGSTerrain* terrain) : __terrain(terrain) {}
  virtual void oneMove(SGSHero* hero) = 0;
protected:
  SGSTerrain* __terrain;
};

#endif