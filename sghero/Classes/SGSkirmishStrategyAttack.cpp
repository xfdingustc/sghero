#include "SGSkirmishStrategyAttack.h"


void SGSkirmishStrategyAttack::oneMove(SGSkirmishHero* hero)
{
  typedef SGSkirmishHero::SGSkirmishHeroList HeroList;

  HeroList* hero_list = __terrain->findAssaultableEnemyHeroes(hero);

  HeroList::iterator iter;

  for (iter = hero_list->begin(); iter != hero_list->end(); iter++) {
    SGSkirmishHero* enemy_hero = *iter;
    log("%s is in %s attack area", enemy_hero->getName().c_str(), hero->getName().c_str());

  }
  hero->setActive(false);
}
