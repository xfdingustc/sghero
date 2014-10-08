#include "SGSStrategyStay.h"


void SGSStrategyStay::oneMove(SGSHero* hero)
{
  notifyObserver("hero_move_finished", NULL);
  hero->setActive(false);
}
