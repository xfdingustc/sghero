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
  for (int i = 0; i < 20; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, HERO_DRAMA_RES_HEIGHT * i, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
    frame->retain();
    __south_sprite_frames.pushBack(frame);
  }
   
  
  __frame_map["putong_south"] = __south_sprite_frames.at(0);
  __frame_map["xiagui_south"] = __south_sprite_frames.at(3);
  __frame_map["lianhong_south"] = __south_sprite_frames.at(4);
  __frame_map["jushou_south"] = __south_sprite_frames.at(5);
  __frame_map["zuoyi_south"] = __south_sprite_frames.at(8);
  __frame_map["panzuoku_south"] = __south_sprite_frames.at(11);
  __frame_map["danshoujuqi_south"] = __south_sprite_frames.at(19);

  Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>;
  animFrames->pushBack(__south_sprite_frames.at(0));
  animFrames->pushBack(__south_sprite_frames.at(1));
  animFrames->pushBack(__south_sprite_frames.at(2));
  Animation* animation = Animation::createWithSpriteFrames(*animFrames, 0.2f);
  Animate* animate = Animate::create(animation);
  animate->retain();
  std::string animate_name = "walk_south";
  __animate_map[animate_name] = animate;

  


  // parse face north resource picture
  hero_res_file = hero_res_obj->drama_scene_north;
  hero_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(hero_res_file);
  Texture2D* north_texture = TextureCache::getInstance()->addImage(hero_res_file_full_path);
  for (int i = 0; i < 20; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(north_texture, Rect(0, HERO_DRAMA_RES_HEIGHT * i, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
    frame->retain();
    __north_sprite_frames.pushBack(frame);
  }
  
  
  __frame_map["putong_north"] = __north_sprite_frames.at(0);
  __frame_map["xiagui_north"] = __north_sprite_frames.at(3);
  __frame_map["lianhong_north"] = __north_sprite_frames.at(4);
  __frame_map["jushou_north"] = __north_sprite_frames.at(5);
  __frame_map["zuoyi_north"] = __north_sprite_frames.at(8);
  __frame_map["panzuoku_north"] = __north_sprite_frames.at(11);
  __frame_map["danshoujuqi_north"] = __north_sprite_frames.at(19);

  Vector<SpriteFrame*>* walk_north_animFrames = new Vector<SpriteFrame*>;
  walk_north_animFrames->pushBack(__north_sprite_frames.at(0));
  walk_north_animFrames->pushBack(__north_sprite_frames.at(1));
  walk_north_animFrames->pushBack(__north_sprite_frames.at(2));
  Animation* walk_north_animation = Animation::createWithSpriteFrames(*walk_north_animFrames, 0.2f);
  Animate* walk_north_animate = Animate::create(walk_north_animation);
  walk_north_animate->retain();
  animate_name = "walk_north";
  __animate_map[animate_name] = walk_north_animate;
  
  this->setName(hero_name);

  this->setScale(1.6);
  //this->setAnchorPoint(Vec2::ZERO);

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
  case DIRECTION_WEST:
    walk_animate_name = "walk_north";
    break;
  case DIRECTION_SOUTH:
  case DIRECTION_EAST:
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

void SGDramaSceneHero::doAction(const char* action)
{
  std::string act = action;
  std::string suffex;
  switch (__face_direction)
  {
  case DIRECTION_NORTH:
  case DIRECTION_WEST:
    suffex = "_north";
    break;
  case DIRECTION_EAST:
  case DIRECTION_SOUTH:
    suffex = "_south";
    break;
  default:
    break;
  }
  
  act.append(suffex);
  SpriteFrame* frame = __frame_map[act];
  if (frame) {
    setSpriteFrame(frame);
  }

}

void SGDramaSceneHero::faceTo(const char* direction)
{
  std::string face_frame_name;
  __face_direction = getDirection(direction);
  switch (__face_direction)
  {
  case DIRECTION_WEST:
    setFlippedX(true);
    break;
  case DIRECTION_NORTH:
    setFlippedX(false);
    break;
  case DIRECTION_SOUTH:
    setFlippedX(false);
    break;
  case DIRECTION_EAST:
    setFlippedX(true);
    break;
  default:
    break;
  }
  doAction("putong");
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