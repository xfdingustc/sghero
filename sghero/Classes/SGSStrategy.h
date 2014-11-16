#ifndef SG_SKIRMIHSH_HERO_MOVE_STRATEGY_H
#define SG_SKIRMIHSH_HERO_MOVE_STRATEGY_H
#include <functional>
#include "cocos2d.h"
USING_NS_CC;

#include "SGObserver.h"
#include "SGSHero.h"
#include "SGSTerrain.h"

NS_CC_BEGIN

class SGSStrategy 
{
public:
  static SGSStrategy* createStrategy(SGSHero::HERO_AI ai, SGSTerrain* terrain);
  SGSStrategy(SGSTerrain* terrain);
  virtual bool oneMove(SGSHero* hero) = 0;
protected:
  SGSTerrain* __terrain;
};
NS_CC_END
#endif