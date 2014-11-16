#include "SGSStrategyAttack.h"
#include "CCLuaEngine.h"

using namespace CocosDenshion;


SGSHeroList* SGSStrategyAttack::findAssaultableEnemyHeroes(SGSHero* hero)
{
  static SGSHeroList assaultable_heroes;
  SGSHeroList::iterator iter;

  // clear the list;
  for (iter = assaultable_heroes.begin(); iter != assaultable_heroes.end();) {
    iter = assaultable_heroes.erase(iter);
  }

  SGSPointList& valid_walk_point_list = __terrain->calcHeroAvailabePath(hero);
  SGSPointList::iterator walk_area_iter;
  SGSPointList::iterator attack_area_iter;

  for (walk_area_iter = valid_walk_point_list.begin(); walk_area_iter != valid_walk_point_list.end(); walk_area_iter++) {
    SGSPoint one_valid_move_pos = *walk_area_iter;
    SGSPointList* attack_area = hero->getAttackAreaFromPosition(Vec2(one_valid_move_pos.x, one_valid_move_pos.y));
    for (attack_area_iter = attack_area->begin(); attack_area_iter != attack_area->end(); attack_area_iter++) {
      SGSPoint one_attack_pos = *attack_area_iter;
      SGSHero* one_hero = __terrain->findHeroByPosition(one_attack_pos);
      if (one_hero && hero->isRival(one_hero)) {
        SGSHeroList::iterator hero_iter;
        bool already_in_list = false;
        for (hero_iter = assaultable_heroes.begin(); hero_iter != assaultable_heroes.end(); hero_iter++) {
          SGSHero* one_list_in_list = *hero_iter;
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


SGSPoint& SGSStrategyAttack::findBestAttackPoint(SGSHero* attack_hero, SGSHero* defend_hero)
{
  SGSPointList& pos_list = __terrain->calcHeroAvailabePath(attack_hero);
  SGSPointList::iterator iter;

  static SGSPoint best_attack_point = attack_hero->getMapPosition();
  
  for (iter = pos_list.begin(); iter != pos_list.end(); iter++) {
    SGSPoint one_point = *iter;
    SGSPointList* attack_area = attack_hero->getAttackAreaFromPosition(Vec2(one_point.x, one_point.y));
    SGSPointList::iterator attack_iter;
    for (attack_iter = attack_area->begin(); attack_iter != attack_area->end(); attack_iter++) {
      SGSPoint one_attack_point = *attack_iter;
      if (one_attack_point == defend_hero->getMapPosition()) {
        best_attack_point = one_point;
      }
    }
  }

  return best_attack_point;
}

SGSHero* SGSStrategyAttack::getBestAssaultHero(SGSHero* hero)
{

  SGSHeroList* hero_list = findAssaultableEnemyHeroes(hero);

  SGSHeroList::iterator iter;

  for (iter = hero_list->begin(); iter != hero_list->end(); iter++) {
    SGSHero* enemy_hero = *iter;

  }
  if (!hero_list->empty()) { 
    return hero_list->front();
  } else {
    return NULL;
  }
}





bool SGSStrategyAttack::oneMove(SGSHero* hero)
{

  SGSHero* best_assaultable_hero = getBestAssaultHero(hero);
  if (best_assaultable_hero) {
    log("%s is going to attack %s ", hero->getName().c_str(), best_assaultable_hero->getName().c_str());
    SGSPoint best_attacked_point = findBestAttackPoint(hero, best_assaultable_hero);
    hero->moveTo(&best_attacked_point);
#if 0
    hero->attackHero(best_assaultable_hero);
#else
    LuaEngine* pEngine = LuaEngine::getInstance();
    pEngine->getLuaStack()->pushObject(hero, "Node");
    //pEngine->getLuaStack()->pushObject(best_assaultable_hero, "SGHero");
    pEngine->executeGlobalFunction("HeroAttack", 1);
#endif
    return false;
  } else {
    return true;
  }
}
