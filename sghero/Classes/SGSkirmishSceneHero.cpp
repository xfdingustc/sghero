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

  if (!hero_res_obj) {
    // we cannot found by hero name, so we need to remove the index
    std::string new_hero_name = hero_name;
    std::string index = "00";
    new_hero_name = new_hero_name.substr(0, new_hero_name.size() - index.size());
    hero_res_obj = utils->getHeroResObj(new_hero_name);
    if (!hero_res_obj) {
      return false;
    }
  }

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

  if (!FileUtils::getInstance()->isFileExist(hero_res_file)) {
    // use default resource;
    hero_res_file = SG_SKIRMISH_SCENE_HERO_RES_PATH;
    hero_res_file.append(hero_res_obj->catagory);
    if (HERO_SIDE_FRIEND == side) {
      hero_res_file.append("_friend");
    } else if (HERO_SIDE_ENEMY == side) {
      hero_res_file.append("_enemy");
    }
    hero_res_file.append(".png");
  }

  std::string hero_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(hero_res_file);
  // Init hero start pic
  if (!Sprite::initWithFile(hero_res_file_full_path, Rect(0, 0, SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT))) {
    return false;
  }

  Texture2D* texture = TextureCache::getInstance()->addImage(hero_res_file_full_path);
  for (int i = 0; i < 11; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(
        texture, Rect(0, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT * i, 
        SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT));
    frame->retain();
    __sprite_frames.pushBack(frame);
  }

  Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>;
  animFrames->pushBack(__sprite_frames.at(0));
  animFrames->pushBack(__sprite_frames.at(1));
  Animation* animation = Animation::createWithSpriteFrames(*animFrames, 0.2f);
  Animate* animate = Animate::create(animation);
  animate->retain();
  std::string animate_name = "face_south";
  __animate_map[animate_name] = animate;

  Vector<SpriteFrame*>* animFrames_north = new Vector<SpriteFrame*>;
  animFrames_north->pushBack(__sprite_frames.at(2));
  animFrames_north->pushBack(__sprite_frames.at(3));
  Animation* animation_north = Animation::createWithSpriteFrames(*animFrames_north, 0.2f);
  Animate* animate_north = Animate::create(animation_north);
  animate_north->retain();
  animate_name = "face_north";
  __animate_map[animate_name] = animate_north;

  Vector<SpriteFrame*>* animFrames_west = new Vector<SpriteFrame*>;
  animFrames_west->pushBack(__sprite_frames.at(4));
  animFrames_west->pushBack(__sprite_frames.at(5));
  Animation* animation_west = Animation::createWithSpriteFrames(*animFrames_west, 0.2f);
  Animate* animate_west = Animate::create(animation_west);
  animate_west->retain();
  animate_name = "face_west";
  __animate_map[animate_name] = animate_west;


  this->setAnchorPoint(Vec2(0.0f, 1.0f));

  this->setName(hero_name);
}

void SGSkirmishSceneHero::faceTo(const char* direction)
{
  __face_direction = getDirection(direction);
  std::string action_name;
  switch (__face_direction)
  {
  case DIRECTION_EAST:
    setFlippedX(true);
    action_name = "face_west";
    break;
  case DIRECTION_WEST:
    setFlippedX(false);
    action_name = "face_west";
    break;
  case DIRECTION_NORTH:
    setFlippedX(false);
    action_name = "face_north";
    break;
  case DIRECTION_SOUTH:
    setFlippedX(false);
    action_name = "face_south";
    break;
  default:
    break;
  }
  
  Animate* animate = __animate_map[action_name];
  RepeatForever* face_walk = RepeatForever::create(animate);
  this->runAction(face_walk);
  
}

SGSkirmishSceneHero::DIRECTION SGSkirmishSceneHero::getDirection(const char* direction)
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