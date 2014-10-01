#include "SGSkirmishHero.h"
#include "SGHeroResourceUtils.h"
#include "SGGlobalSettings.h"
#include "SGSkirmishScene.h"

SGSkirmishHero* SGSkirmishHero::create(const char* hero_name, HERO_SIDE side, SGObserver* observer)
{
  SGSkirmishHero* hero = new SGSkirmishHero(observer);

  if (hero && hero->init(hero_name, side)) {
    hero->autorelease();
    return hero;
  } else {
    delete hero;
    return NULL;
  }
}

bool SGSkirmishHero::init(const char* hero_name, HERO_SIDE side)
{
  if (!Sprite::init()) {
    return false;
  }

  __name = hero_name;
  __side = side;

  __active = true;

  initActions();
  initAttackActions();
  initSpecActions();

  this->setAnchorPoint(Vec2(0.5f, 0.5f));

  this->setName(hero_name);
  notifyObserver("hero_add", reinterpret_cast<void*>(this));

  // init catagory
  initCatagory();
  

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  __event_listener = EventListenerTouchOneByOne::create();
  __event_listener->onTouchBegan = CC_CALLBACK_2(SGSkirmishHero::onTouchBegin, this);
  __event_listener->setSwallowTouches(true);
  dispatcher->addEventListenerWithSceneGraphPriority(__event_listener, this);
}

bool SGSkirmishHero::onTouchBegin(Touch *touch, Event *unused_event)
{
  Vec2 touchPoint = touch->getLocation();
  Vec2 reallyPoint = this->getParent()->convertToNodeSpace(touchPoint);
  Rect rect = this->getBoundingBox();

  if(rect.containsPoint(reallyPoint)){
    CCLOG("%s touched", this->getName().c_str());
    showAvailablePath();
    return true;
  }
 
  return false;
}

void SGSkirmishHero::showAvailablePath()
{
  SGSkirmishScene* skrimish = (SGSkirmishScene*)this->getParent();
  skrimish->showHeroAvailabePath(this);
}

bool SGSkirmishHero::isRival(SGSkirmishHero* hero)
{
  if (!hero) {
    return false;
  }
  switch (this->__side)
  {
  case HERO_SIDE_OURS:
  case HERO_SIDE_FRIEND:
    if (hero->__side == HERO_SIDE_OURS || hero->__side == HERO_SIDE_FRIEND) {
      return false;
    } else {
      return true;
    }
    break;
  case HERO_SIDE_ENEMY:
    if (hero->__side == HERO_SIDE_ENEMY) {
      return false;
    } else {
      return true;
    }
    break;
  default:
    return false;
    break;
  }
}

bool SGSkirmishHero::initActions()
{
  std::string hero_res_file_full_path = getHeroResFile(SG_SKIRMISH_SCENE_HERO_RES_PATH);
  // Init hero start picture
  if (!Sprite::initWithFile(hero_res_file_full_path, Rect(0, 0, SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT))) {
    return false;
  }

  Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(hero_res_file_full_path);
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

  Vector<SpriteFrame*>* fragile = new Vector<SpriteFrame*>;
  fragile->pushBack(__sprite_frames.at(9));
  Animation* animation_fragile = Animation::createWithSpriteFrames(*fragile, 1.0f);
  Animate* animate_fragile = Animate::create(animation_fragile);
  animate_fragile->retain();
  animate_name = "fragile";
  __animate_map[animate_name] = animate_fragile;


  Vector<SpriteFrame*>* wheeze = new Vector<SpriteFrame*>;
  wheeze->pushBack(__sprite_frames.at(9));
  wheeze->pushBack(__sprite_frames.at(10));
  Animation* animation_wheeze = Animation::createWithSpriteFrames(*wheeze, 0.2f);
  Animate* animate_wheeze = Animate::create(animation_wheeze);
  animate_wheeze->retain();
  animate_name = "wheeze";
  __animate_map[animate_name] = animate_wheeze;
  return true;
}

bool SGSkirmishHero::initAttackActions()
{
  std::string hero_attack_res_file_full_path = getHeroResFile(SG_SKIRMISH_SCENE_HERO_ATTACK_RES_PATH);

  Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(hero_attack_res_file_full_path);
  for (int i = 0; i < 12; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(
      texture, Rect(0, SG_SKIRMISH_SCENE_HERO_ATTACK_RES_HEIGHT * i, 
      SG_SKIRMISH_SCENE_HERO_ATTACK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_ATTACK_RES_HEIGHT));
    frame->retain();
    __attack_sprite_frames.pushBack(frame);
  }

  Vector<SpriteFrame*>* animFrames_south = new Vector<SpriteFrame*>;
  animFrames_south->pushBack(__attack_sprite_frames.at(0));
  animFrames_south->pushBack(__attack_sprite_frames.at(1));
  animFrames_south->pushBack(__attack_sprite_frames.at(2));
  animFrames_south->pushBack(__attack_sprite_frames.at(3));
  Animation* animation_south = Animation::createWithSpriteFrames(*animFrames_south, 0.2f);
  Animate* animate_south = Animate::create(animation_south);
  animate_south->retain();
  std::string animate_name = "attack_south";
  __animate_map[animate_name] = animate_south;

  Vector<SpriteFrame*>* animFrames_north = new Vector<SpriteFrame*>;
  animFrames_north->pushBack(__attack_sprite_frames.at(4));
  animFrames_north->pushBack(__attack_sprite_frames.at(5));
  animFrames_north->pushBack(__attack_sprite_frames.at(6));
  animFrames_north->pushBack(__attack_sprite_frames.at(7));
  Animation* animation_north = Animation::createWithSpriteFrames(*animFrames_north, 0.2f);
  Animate* animate_north = Animate::create(animation_north);
  animate_north->retain();
  animate_name = "attack_north";
  __animate_map[animate_name] = animate_north;

  Vector<SpriteFrame*>* animFrames_west = new Vector<SpriteFrame*>;
  animFrames_west->pushBack(__attack_sprite_frames.at(8));
  animFrames_west->pushBack(__attack_sprite_frames.at(9));
  animFrames_west->pushBack(__attack_sprite_frames.at(10));
  animFrames_west->pushBack(__attack_sprite_frames.at(11));
  Animation* animation_west = Animation::createWithSpriteFrames(*animFrames_west, 0.2f);
  Animate* animate_west = Animate::create(animation_west);
  animate_west->retain();
  animate_name = "attack_west";
  __animate_map[animate_name] = animate_west;

  return true;
}

bool SGSkirmishHero::initSpecActions()
{
  std::string hero_spec_res_file_full_path = getHeroResFile(SG_SKIRMISH_SCENE_HERO_SPEC_RES_PATH);
  Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(hero_spec_res_file_full_path);
  for (int i = 0; i < 5; i++) {
    SpriteFrame* frame = SpriteFrame::createWithTexture(
      texture, Rect(0, SG_SKIRMISH_SCENE_HERO_SPEC_RES_WIDTH * i, 
      SG_SKIRMISH_SCENE_HERO_SPEC_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_SPEC_RES_HEIGHT));
    frame->retain();
    __spec_sprite_frames.pushBack(frame);
  }
  Vector<SpriteFrame*>* block_south = new Vector<SpriteFrame*>;
  block_south->pushBack(__spec_sprite_frames.at(0));
  Animation* animation_south = Animation::createWithSpriteFrames(*block_south, 0.5f);
  Animate* animate_south = Animate::create(animation_south);
  animate_south->retain();
  std::string animate_name = "block_south";
  __animate_map[animate_name] = animate_south;

  Vector<SpriteFrame*>* block_north = new Vector<SpriteFrame*>;
  block_north->pushBack(__spec_sprite_frames.at(1));
  Animation* animation_north = Animation::createWithSpriteFrames(*block_north, 0.5f);
  Animate* animate_north = Animate::create(animation_north);
  animate_north->retain();
  animate_name = "block_north";
  __animate_map[animate_name] = animate_north;

  Vector<SpriteFrame*>* block_west = new Vector<SpriteFrame*>;
  block_west->pushBack(__spec_sprite_frames.at(2));
  Animation* animation_west = Animation::createWithSpriteFrames(*block_west, 0.5f);
  Animate* animate_west = Animate::create(animation_west);
  animate_west->retain();
  animate_name = "block_west";
  __animate_map[animate_name] = animate_west;

  Vector<SpriteFrame*>* attacked = new Vector<SpriteFrame*>;
  attacked->pushBack(__spec_sprite_frames.at(3));
  Animation* animation_attacked = Animation::createWithSpriteFrames(*attacked, 1.0f);
  Animate* animate_attack = Animate::create(animation_attacked);
  animate_attack->retain();
  animate_name = "attacked";
  __animate_map[animate_name] = animate_attack;
  return true;
}

void SGSkirmishHero::initCatagory()
{
  std::string catagory = SGHeroResourceUtils::getInstance()->getHeroResObj(__name)->catagory;
  if (catagory == "lord") {
    __catagory = HERO_CATAGORY_LORD;
  } else if (catagory == "infantry") {
    __catagory = HERO_CATAGORY_INFANTRY;
  } else if (catagory == "archer" ) {
    __catagory = HERO_CATAGORY_ARCHER;
  } else if (catagory == "knight") {
    __catagory = HERO_CATAGORY_ARCHER;
  } else if (catagory == "horsearcher") {
    __catagory = HERO_CATAGORY_HORSEARCHER;
  } else if (catagory == "demolisher") {
    __catagory = HERO_CATAGORY_DEMOLISHER;
  } else if (catagory == "martialist") {
    __catagory = HERO_CATAGORY_MARTIALIST;
  } else if (catagory == "thief") {
    __catagory = HERO_CATAGORY_THIEF;
  } else if (catagory == "mage") {
    __catagory = HERO_CATAGORY_MAGE;
  } else if (catagory == "priest") {
    __catagory = HERO_CATAGORY_PRIEST;
  } else if (catagory == "warlock") {
    __catagory = HERO_CATAGORY_WARLOCK;
  } else if (catagory == "horsemage") {
    __catagory = HERO_CATAGORY_HORSEMAGE;
  } else if (catagory == "dancer") {
    __catagory = HERO_CATAGORY_DANCER;
  }

}

void SGSkirmishHero::initDataNum()
{
  __stamina = 6;
}

std::string& SGSkirmishHero::getHeroResFile(const char* res_dir)
{
  static std::string res_file;

  SGHeroResourceUtils::SGHeroResourceObject* hero_res_obj = SGHeroResourceUtils::getInstance()->getHeroResObj(__name);
  std::string hero_res_file = res_dir;

  if (!hero_res_obj) {
    // we cannot found by hero name, so we need to remove the index
    std::string new_hero_name = __name;
    std::string index = "00";
    new_hero_name = new_hero_name.substr(0, new_hero_name.size() - index.size());
    hero_res_obj = SGHeroResourceUtils::getInstance()->getHeroResObj(new_hero_name);
    if (!hero_res_obj) {
      res_file = "";
      return res_file;
    }
  }
  if (hero_res_obj->res_name.empty()) {
    // use default resource
    hero_res_file.append(hero_res_obj->catagory);
    // add side info
    if (HERO_SIDE_FRIEND == __side) {
      hero_res_file.append("_friend");
    } else if (HERO_SIDE_ENEMY == __side) {
      hero_res_file.append("_enemy");
    }
  } else {
    hero_res_file.append(hero_res_obj->res_name);
  }
  
  hero_res_file.append(".png");
  

  if (!FileUtils::getInstance()->isFileExist(hero_res_file)) {
    // use default resource;
    hero_res_file = res_dir;
    hero_res_file.append(hero_res_obj->catagory);
    if (HERO_SIDE_FRIEND == __side) {
      hero_res_file.append("_friend");
    } else if (HERO_SIDE_ENEMY == __side) {
      hero_res_file.append("_enemy");
    }
    hero_res_file.append(".png");
  }
  res_file = FileUtils::getInstance()->fullPathForFilename(hero_res_file);
  return res_file;
}

void SGSkirmishHero::faceTo(const char* direction)
{
  this->stopAllActions();
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
void SGSkirmishHero::moveTo(SGSkirmishMapPos& target_pos)
{
  this->setMapPosition(target_pos);
}


void SGSkirmishHero::doAttackAction()
{
  std::string action_name;
  switch (__face_direction)
  {
  case DIRECTION_NORTH:
    action_name = "attack_north";
    break;
  case DIRECTION_SOUTH:
    action_name = "attack_south";
    break;
  case DIRECTION_EAST:
    action_name = "attack_west";
    break;
  case DIRECTION_WEST:
    action_name = "attack_west";
    break;
  default:
    break;
  }
  Animate* animate = __animate_map[action_name];
  this->runAction(animate);
}

void SGSkirmishHero::doAction(const char* action)
{
  this->stopAllActions();
  if (!strcmp(action, "attack")) {
    doAttackAction();
  } else if (!strcmp(action, "attacked")) {
    std::string action_name = "attacked";
    Animate* animate = __animate_map[action_name];
    this->runAction(animate);
  } else if (!strcmp(action, "fragile")) {
    std::string action_name = "fragile";
    Animate* animate = __animate_map[action_name];
    RepeatForever* animate_repeat = RepeatForever::create(animate);
    this->runAction(animate_repeat);
  } else if (!strcmp(action, "wheeze")) {
    std::string action_name = "wheeze";
    Animate* animate = __animate_map[action_name];
    RepeatForever* animate_repeat = RepeatForever::create(animate);
  }
}

SGSkirmishHero::DIRECTION SGSkirmishHero::getDirection(const char* direction)
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

void SGSkirmishHero::setStatus(std::string& status)
{
  if (status == "chaos") {
    std::string chaos_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(SG_SKIRMISH_SCENE_HERO_STATUS_CHAOS);
    Sprite* chaos_sprite = Sprite::create(chaos_res_file_full_path);
    chaos_sprite->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    chaos_sprite->setPosition(Vec2(SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT));
    this->addChild(chaos_sprite);
  }
}

