#include "SGSkirmishStrategyAttack.h"


void SGSkirmishStrategyAttack::oneMove(SGSkirmishHero* hero)
{
  SGSkirmishHero* best_assaultable_hero = getBestAssaultHero(hero);
  if (best_assaultable_hero) {
    log("%s is going to attack %s ", hero->getName().c_str(), best_assaultable_hero->getName().c_str());
  }

  hero->setActive(false);
}

SGSkirmishHero* SGSkirmishStrategyAttack::getBestAssaultHero(SGSkirmishHero* hero)
{
  typedef SGSkirmishHero::SGSkirmishHeroList HeroList;

  HeroList* hero_list = __terrain->findAssaultableEnemyHeroes(hero);

  HeroList::iterator iter;

  for (iter = hero_list->begin(); iter != hero_list->end(); iter++) {
    SGSkirmishHero* enemy_hero = *iter;

  }
  if (!hero_list->empty()) { 
    return hero_list->front();
  } else {
    return NULL;
  }
}
