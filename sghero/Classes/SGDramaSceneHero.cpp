#include "SGDramaSceneHero.h"
#include "SGHeroResourceUtils.h"

USING_NS_CC;

SGDramaSceneHero* SGDramaSceneHero::create(const char* hero_name)
{
  SGDramaSceneHero* hero = new SGDramaSceneHero;

  if (hero && hero->init(hero_name)) {
    hero->autorelease();
    return hero;
  } else {
    delete hero;
    hero = NULL;
    return NULL;
  }
}

bool SGDramaSceneHero::init(const char* hero_name)
{
  SGHeroResourceUtils* utils = SGHeroResourceUtils::getInstance();
  SGHeroResourceUtils::SGHeroResourceObject* hero_res_obj = utils->getHeroResObj(hero_name);

  std::string hero_res_file = hero_res_obj->drama_scene_south;

  std::string hero_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(hero_res_file);



  if (!Sprite::initWithFile(hero_res_file_full_path, Rect(0, 0, 48, 64))) {
    return false;
  }

  return true;


}