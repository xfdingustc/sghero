#include "SGSkirmishSceneHero.h"
#include "SGHeroResourceUtils.h"
#include "SGGlobalSettings.h"

SGSkirmishSceneHero* SGSkirmishSceneHero::create(const char* hero_name, HERO_SIDE side)
{
  SGSkirmishSceneHero* hero = new SGSkirmishSceneHero();

  if (hero && hero->init(hero_name, side)) {
    hero->autorelease();
    return hero;
  } else {
    delete hero;
    return NULL;
  }
}

bool SGSkirmishSceneHero::init(const char* hero_name, HERO_SIDE side)
{
  if (!Sprite::init()) {
    return false;
  }
  SGHeroResourceUtils* utils = SGHeroResourceUtils::getInstance();
  SGHeroResourceUtils::SGHeroResourceObject* hero_res_obj = utils->getHeroResObj(hero_name);

  std::string hero_res_file = SG_SKIRMISH_SCENE_HERO_RES_PATH;
  
  if (hero_res_obj->res_name.empty()) {
    // use default resource
    hero_res_file.append(hero_res_obj->catagory);
    // add side info
    if (HERO_SIDE_FRIEND == side) {
      hero_res_file.append("_friend");
    } else if (HERO_SIDE_ENEMY == side) {
      hero_res_file.append("_enemy");
    }
  } else {
    hero_res_file.append(hero_res_obj->res_name);
  }
  
  
  hero_res_file.append(".png");

  std::string hero_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(hero_res_file);
  // Init hero start pic
  if (!Sprite::initWithFile(hero_res_file_full_path, Rect(0, 0, SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT))) {
    return false;
  }

  this->setAnchorPoint(Vec2(0.0f, 1.0f));

  this->setName(hero_name);
}