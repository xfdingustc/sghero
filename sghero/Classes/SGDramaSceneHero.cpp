#include "SGDramaSceneHero.h"
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

  std::string hero_res_name = SG_DRAMA_SCENE_HERO_RES_PATH;
  hero_res_name.append(hero_res_obj->res_name);
   
  std::string hero_south = hero_res_name;
  hero_south.append("_south.png");


  std::string hero_south_full_path = FileUtils::getInstance()->fullPathForFilename(hero_south);


  // Init hero start pic
  if (!Sprite::initWithFile(hero_south_full_path, Rect(0, 0, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT))) {
    return false;
  }

  // init hero actions
  // parse face south resource picture
  Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(hero_south_full_path);
  for (int i = 0; i < 20; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect(0, HERO_DRAMA_RES_HEIGHT * i, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
    frame->retain();
    __south_sprite_frames.pushBack(frame);
  }
   
  
  __frame_map["putong_south"] = __south_sprite_frames.at(0);
  __frame_map["xiagui_south"] = __south_sprite_frames.at(3);
  __frame_map["lianhong_south"] = __south_sprite_frames.at(4);
  __frame_map["jushou_south"] = __south_sprite_frames.at(5);
  __frame_map["ku_south"] = __south_sprite_frames.at(6);
  __frame_map["shenshou_south"] = __south_sprite_frames.at(7);
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
  std::string hero_north = hero_res_name;
  hero_north.append("_north.png");
  std::string hero_north_full_path = FileUtils::getInstance()->fullPathForFilename(hero_north);
  Texture2D* north_texture = Director::getInstance()->getTextureCache()->addImage(hero_north_full_path);
  for (int i = 0; i < 20; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(north_texture, Rect(0, HERO_DRAMA_RES_HEIGHT * i, HERO_DRAMA_RES_WIDTH, HERO_DRAMA_RES_HEIGHT));
    frame->retain();
    __north_sprite_frames.pushBack(frame);
  }
  
  
  __frame_map["putong_north"] = __north_sprite_frames.at(0);
  __frame_map["xiagui_north"] = __north_sprite_frames.at(3);
  __frame_map["lianhong_north"] = __north_sprite_frames.at(4);
  __frame_map["jushou_north"] = __north_sprite_frames.at(5);
  __frame_map["ku_north"] = __north_sprite_frames.at(6);
  __frame_map["shenshou_north"] = __north_sprite_frames.at(7);
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

  return true;


}

bool SGDramaSceneHero::initActions()
{
	return true;

	
}

void SGDramaSceneHero::moveTo(Vec2 target_pos, const char* direction)
{
  int actualDuration = 3.0f;
  faceTo(direction);
  FiniteTimeAction *actionMove = MoveTo::create(actualDuration, target_pos);
  CallFunc * funcall= CallFunc::create(this, callfunc_selector(SGDramaSceneHero::actionFinished));
  FiniteTimeAction* moveWithCallback = Sequence::create(actionMove, funcall, NULL);
  std::string walk_animate_name;
  Vec2 cur_pos = this->getPosition();
  DIRECTION move_dir;
  if (target_pos.x > cur_pos.x && target_pos.y < cur_pos.y) {
    move_dir = DIRECTION_EAST;
  } else if (target_pos.x < cur_pos.x && target_pos.y < cur_pos.y) {
    move_dir = DIRECTION_SOUTH;
  } else if (target_pos.x > cur_pos.x && target_pos.y > cur_pos.y) {
    move_dir = DIRECTION_NORTH;
  } else {
    move_dir = DIRECTION_WEST;
  }
  switch (move_dir)
  {
  case DIRECTION_WEST:
    setFlippedX(true);
    walk_animate_name = "walk_north";
    break;
  case DIRECTION_NORTH:
    setFlippedX(false);
    walk_animate_name = "walk_north";
    break;
  case DIRECTION_SOUTH:
    setFlippedX(false);
    walk_animate_name = "walk_south";
    break;
  case DIRECTION_EAST:
    setFlippedX(true);
    walk_animate_name = "walk_south";
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
  
  faceTo(getDirection(direction));
}

void SGDramaSceneHero::faceTo(DIRECTION direction)
{
  __face_direction = direction;
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
  faceTo(__face_direction);
  this->stopAllActions();
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