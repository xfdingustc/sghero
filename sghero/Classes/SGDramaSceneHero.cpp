#include "SGDramaSceneHero.h"
#include "SGDramaSceneHeroSpeakScene.h"
#include "SGHeroResourceUtils.h"
#include "SGGlobalSettings.h"

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
  if (!Sprite::init()) {
    return false;
  }

  SGHeroResourceUtils* utils = SGHeroResourceUtils::getInstance();
  SGHeroResourceUtils::SGHeroResourceObject* hero_res_obj = utils->getHeroResObj(hero_name);

  std::string hero_res_file = hero_res_obj->drama_scene_south;

  std::string hero_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(hero_res_file);


  // Init hero start pic
  if (!Sprite::initWithFile(hero_res_file_full_path, Rect(0, 0, 48, 64))) {
    return false;
  }

  // init hero actions
  // parse face south resource picture
  Texture2D* texture = TextureCache::getInstance()->addImage(hero_res_file_full_path);
  SpriteFrame* frame0 = SpriteFrame::createWithTexture(texture, Rect(0, 0, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
  std::string frame_name = "face_south";
  __frame_map[frame_name] = frame0;
  SpriteFrame* frame1 = SpriteFrame::createWithTexture(texture, Rect(0, HERO_DRAMA_RES_HEIGHT, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
  SpriteFrame* frame2 = SpriteFrame::createWithTexture(texture, Rect(0, HERO_DRAMA_RES_HEIGHT*2, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
  Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>;
  animFrames->pushBack(frame0);
  animFrames->pushBack(frame1);
  animFrames->pushBack(frame2);
  Animation* animation = Animation::createWithSpriteFrames(*animFrames, 0.2f);
  Animate* animate = Animate::create(animation);
  animate->retain();
  std::string animate_name = "walk_south";
  __animate_map[animate_name] = animate;

  // parse face north resource picture
  hero_res_file = hero_res_obj->drama_scene_north;
  hero_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(hero_res_file);
  Texture2D* north_texture = TextureCache::getInstance()->addImage(hero_res_file_full_path);
  SpriteFrame* north_frame0 = SpriteFrame::createWithTexture(north_texture, Rect(0, 0, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
  frame_name = "face_north";
  __frame_map[frame_name] = north_frame0;
  SpriteFrame* north_frame1 = SpriteFrame::createWithTexture(north_texture, Rect(0, HERO_DRAMA_RES_HEIGHT, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
  SpriteFrame* north_frame2 = SpriteFrame::createWithTexture(north_texture, Rect(0, HERO_DRAMA_RES_HEIGHT*2, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
  Vector<SpriteFrame*>* walk_north_animFrames = new Vector<SpriteFrame*>;
  walk_north_animFrames->pushBack(north_frame0);
  walk_north_animFrames->pushBack(north_frame1);
  walk_north_animFrames->pushBack(north_frame2);
  Animation* walk_north_animation = Animation::createWithSpriteFrames(*walk_north_animFrames, 0.2f);
  Animate* walk_north_animate = Animate::create(walk_north_animation);
  walk_north_animate->retain();
  animate_name = "walk_north";
  __animate_map[animate_name] = walk_north_animate;


  this->setName(hero_name);

  return true;


}

bool SGDramaSceneHero::initActions()
{
	return true;

	
}

void SGDramaSceneHero::moveTo(Vec2 target_pos, const char* direction)
{
  int actualDuration = 3.0f;
  //faceTo(direction);
  FiniteTimeAction *actionMove = MoveTo::create(actualDuration, target_pos);
  CallFunc * funcall= CallFunc::create(this, callfunc_selector(SGDramaSceneHero::actionFinished));
  FiniteTimeAction* moveWithCallback = Sequence::create(actionMove, funcall, NULL);
  std::string walk_animate_name;
  switch (getDirection(direction))
  {
  case DIRECTION_NORTH:
    walk_animate_name = "walk_north";
    break;
  case DIRECTION_SOUTH:
    walk_animate_name = "walk_south";
    break;
  default:
    break;
  }

  Animate* animate = __animate_map[walk_animate_name];
  Repeat* walk = Repeat::create(animate, 300);
    
  Spawn * walk_south = Spawn::create(walk, moveWithCallback, NULL);
   
  this->runAction(walk_south);
}

void SGDramaSceneHero::faceTo(const char* direction)
{
  std::string face_frame_name;
  DIRECTION dir = getDirection(direction);
  switch (dir)
  {
  case DIRECTION_WEST:
    setFlippedX(true);
    face_frame_name = "face_north";
    break;
  case DIRECTION_NORTH:
    setFlippedX(false);
    face_frame_name = "face_north";
    break;
  case DIRECTION_SOUTH:
    setFlippedX(false);
    face_frame_name = "face_south";
    break;
  case DIRECTION_EAST:
    setFlippedX(true);
    face_frame_name = "face_south";
    break;
  default:
    break;
  }
  SpriteFrame* frame = __frame_map[face_frame_name];
  setSpriteFrame(frame);

}

void SGDramaSceneHero::actionFinished()
{
  this->stopAllActions();
}

void SGDramaSceneHero::speak(const char* content)
{
  Scene* scene = SGDramaSceneHeroSpeakScene::creatScene(getName().c_str(), content);
  Director::getInstance()->pushScene(scene);
}

SGDramaSceneHero::DIRECTION SGDramaSceneHero::getDirection(const char* direction)
{
  if (!strcmp(direction, "north")) {
    return DIRECTION_NORTH;
  } else if (!strcmp(direction, "south")) {
    return DIRECTION_SOUTH;
  } else if (!strcmp(direction, "east")) {
    return DIRECTION_EAST;
  } else if (!strcmp(direction, "west")) {
    return DIRECTION_WEST;
  }

  return DIRECTION_NORTH;
}