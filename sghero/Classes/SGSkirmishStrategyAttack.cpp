#include "SGSkirmishStrategyAttack.h"


void SGSkirmishStrategyAttack::oneMove(SGSkirmishHero* hero)
{
  SGSkirmishHero* best_assaultable_hero = getBestAssaultHero(hero);
  if (best_assaultable_hero) {
    log("%s is going to attack %s ", hero->getName().c_str(), best_assaultable_hero->getName().c_str());
  }
  //SGSkirmishMapPos pos = __terrain->calcHeroAvailabePath()
  hero->setActive(false);
}

SGSkirmishHero* SGSkirmishStrategyAttack::getBestAssaultHero(SGSkirmishHero* hero)
{

  SGSkirmishHeroList* hero_list = findAssaultableEnemyHeroes(hero);

  SGSkirmishHeroList::iterator iter;

  for (iter = hero_list->begin(); iter != hero_list->end(); iter++) {
    SGSkirmishHero* enemy_hero = *iter;

  }
  if (!hero_list->empty()) { 
    return hero_list->front();
  } else {
    return NULL;
  }
}


SGSkirmishHeroList* SGSkirmishStrategyAttack::findAssaultableEnemyHeroes(SGSkirmishHero* hero)
{
  static SGSkirmishHeroList assaultable_heroes;
  SGSkirmishHeroList::iterator iter;

  // clear the list;
  for (iter = assaultable_heroes.begin(); iter != assaultable_heroes.end();) {
    iter = assaultable_heroes.erase(iter);
  }

  SGSkirmishPointList& valid_walk_point_list = __terrain->calcHeroAvailabePath(hero);
  SGSkirmishPointList::iterator walk_area_iter;
  SGSkirmishPointList::iterator attack_area_iter;

  for (walk_area_iter = valid_walk_point_list.begin(); walk_area_iter != valid_walk_point_list.end(); walk_area_iter++) {
    SGSkirmishMapPos one_valid_move_pos = *walk_area_iter;
    SGSkirmishPointList* attack_area = hero->getAttackAreaFromPosition(one_valid_move_pos);
    for (attack_area_iter = attack_area->begin(); attack_area_iter != attack_area->end(); attack_area_iter++) {
      SGSkirmishMapPos one_attack_pos = *attack_area_iter;
      SGSkirmishHero* one_hero = __terrain->findHeroByPosition(one_attack_pos);
      if (one_hero && hero->isRival(one_hero)) {
        SGSkirmishHeroList::iterator hero_iter;
        bool already_in_list = false;
        for (hero_iter = assaultable_heroes.begin(); hero_iter != assaultable_heroes.end(); hero_iter++) {
          SGSkirmishHero* one_list_in_list = *hero_iter;
          if (one_list_in_list == one_hero) {
            already_in_list = true;
            break;
          }
        }
        if (!already_in_list) {
          assaultable_heroes.pushBack(one_hero);
        }
        break;
      }

    }
  }
  return &assaultable_heroes;
}
