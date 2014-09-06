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


  // Init hero start pic
  if (!Sprite::initWithFile(hero_res_file_full_path, Rect(0, 0, 48, 64))) {
    return false;
  }

  // init hero actions
  Texture2D* texture = TextureCache::getInstance()->addImage(hero_res_file_full_path);
  SpriteFrame* frame0 = SpriteFrame::createWithTexture(texture, Rect(0, 0, 48, 64));
  SpriteFrame* frame1 = SpriteFrame::createWithTexture(texture, Rect(0, 64, 48, 64));
  SpriteFrame* frame2 = SpriteFrame::createWithTexture(texture, Rect(0, 128, 48, 64));

  Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>;
  animFrames->pushBack(frame0);
  animFrames->pushBack(frame1);
  animFrames->pushBack(frame2);

  Animation* animation = Animation::createWithSpriteFrames(*animFrames, 0.2f);

  animate = Animate::create(animation);

  animate->retain();


  this->setName(hero_name);

  return true;


}

bool SGDramaSceneHero::initActions()
{
	return true;

	
}

void SGDramaSceneHero::moveTo(Vec2 target_pos)
{
  int actualDuration = 3;
  FiniteTimeAction *actionMove = MoveTo::create(actualDuration, target_pos);
  CallFunc * funcall= CallFunc::create(this, callfunc_selector(SGDramaSceneHero::actionFinished));
  FiniteTimeAction* moveWithCallback = Sequence::create(actionMove, funcall, NULL);

  //this->runAction(actionMove);
  Repeat* walk = Repeat::create(animate, 300);
    
  Spawn * walk_south = Spawn::create(walk, moveWithCallback, NULL);
   
  this->runAction(walk_south);
}

void SGDramaSceneHero::actionFinished()
{
  this->stopAllActions();
  CCLOG("Action finished");
}