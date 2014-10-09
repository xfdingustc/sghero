#include "SGSHero.h"
#include "SGHeroResourceUtils.h"
#include "SGGlobalSettings.h"
#include "SGSkirmishScene.h"
#include "SGSStrategy.h"

SGSHeroActionFinishedCallback SGSHero::__move_finished_callback;


void SGSHero::attackActionFinished(Node* hero, void* ptr)
{
  SGSHero* enemy_hero = (SGSHero*)ptr;

  // counterattack
  enemy_hero->setDirection(enemy_hero->getRelativeDirection(this));
  Animate* counter_attack_animate = enemy_hero->getAttackAnimate();
  __CCCallFuncND * funcall= __CCCallFuncND::create(enemy_hero, callfuncND_selector(SGSHero::counterAttackFinished, this), this);
  FiniteTimeAction* counterAttackWithCallback = Sequence::create(counter_attack_animate, funcall, NULL);
  enemy_hero->stopAllActions();
  enemy_hero->runAction(counterAttackWithCallback);
  this->doAction("attacked");
}


void SGSHero::attackHero(SGSHero* defense_hero)
{
  // attack
  setDirection(getRelativeDirection(defense_hero));
  Animate* attack_animate = this->getAttackAnimate();
  __CCCallFuncND * funcall= __CCCallFuncND::create(this, callfuncND_selector(SGSHero::attackActionFinished, this), defense_hero);
  FiniteTimeAction* attackWithCallback = Sequence::create(attack_animate, funcall, NULL);
  this->stopAllActions();
  this->runAction(attackWithCallback);
  defense_hero->doAction("attacked");
}

void SGSHero::counterAttackFinished(Node* hero, void* ptr)
{
  SGSHero* enemy_hero = (SGSHero*)ptr;
  enemy_hero->updataSprite();  
  enemy_hero->setActive(false);

  log("%s %s", this->getName().c_str(), enemy_hero->getName().c_str());
  updataSprite();
  if (SGSHero::__move_finished_callback) {
    SGSHero::__move_finished_callback();
  }
}


SGSHero* SGSHero::create(const char* hero_name, HERO_SIDE side, SGObserver* observer)
{
  SGSHero* hero = new SGSHero(observer);

  if (hero && hero->init(hero_name, side)) {
    hero->autorelease();
    return hero;
  } else {
    delete hero;
    return NULL;
  }
}

bool SGSHero::init(const char* hero_name, HERO_SIDE side)
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
  
  __status = HERO_STATUS_NORMAL;
  __ai = HERO_AI_ATTACK;
  initDataNum();
  return true;
  
}

bool SGSHero::isRival(SGSHero* hero)
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

bool SGSHero::initActions()
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

bool SGSHero::initAttackActions()
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

bool SGSHero::initSpecActions()
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

void SGSHero::initCatagory()
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

void SGSHero::initDataNum()
{
  __stamina = 6;
}

std::string& SGSHero::getHeroResFile(const char* res_dir)
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

void SGSHero::faceTo(const char* direction)
{
  faceTo(getDirection(direction));
}

void SGSHero::faceTo(HERO_DIRECTION direction)
{
  setDirection(direction);
  stopAllActions();
  std::string action_name;
  switch (__direction)
  {
  case HERO_DIRECTION_EAST:
    action_name = "face_west";
    break;
  case HERO_DIRECTION_WEST:
    action_name = "face_west";
    break;
  case HERO_DIRECTION_NORTH:
    action_name = "face_north";
    break;
  case HERO_DIRECTION_SOUTH:
    action_name = "face_south";
    break;
  default:
    break;
  }

  Animate* animate = __animate_map[action_name];
  RepeatForever* face_walk = RepeatForever::create(animate);
  this->runAction(face_walk);
}

void SGSHero::moveTo(SGSPoint& target_pos)
{
  this->setMapPosition(target_pos);
}

void SGSHero::oneAIMove(const SGSHeroActionFinishedCallback& callback, SGSTerrain* terrain)
{
  setActionFinishedCallback(callback);
  HERO_AI hero_ai = getAI();
  SGSStrategy* strategy = SGSStrategy::createStrategy(hero_ai, terrain);
  bool ret = strategy->oneMove(this);
  if (ret) {
    setActive(false);
    if (SGSHero::__move_finished_callback) {
      __move_finished_callback();
    }
  }
  
}


Animate* SGSHero::getAttackAnimate()
{
  std::string action_name;
  switch (__direction)
  {
  case HERO_DIRECTION_NORTH:
    action_name = "attack_north";
    break;
  case HERO_DIRECTION_SOUTH:
    action_name = "attack_south";
    break;
  case HERO_DIRECTION_EAST:
    action_name = "attack_west";
    break;
  case HERO_DIRECTION_WEST:
    action_name = "attack_west";
    break;
  default:
    break;
  }
  return __animate_map[action_name];
}


SGSHero::HERO_DIRECTION SGSHero::getRelativeDirection(SGSHero* other_hero)
{
  HERO_DIRECTION direction;
  Vec2 hero_pos = this->getPosition();
  Vec2 target_hero_pos = other_hero->getPosition();


  if (target_hero_pos.x > hero_pos.x) {
    direction = HERO_DIRECTION_EAST;
  } else if (target_hero_pos.x < hero_pos.x) {
    direction = HERO_DIRECTION_WEST;
  } else if (target_hero_pos.y > hero_pos.y) {
    direction = HERO_DIRECTION_NORTH;
  } else {
    direction = HERO_DIRECTION_SOUTH;
  }

  return direction;

}


void SGSHero::doAttackAction()
{
  this->runAction(getAttackAnimate());
}

void SGSHero::doAction(const char* action)
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

SGSHero::HERO_DIRECTION SGSHero::getDirection(const char* direction)
{
  if (!strcmp(direction, "north")) {
    return HERO_DIRECTION_NORTH;
  } else if (!strcmp(direction, "south")) {
    return HERO_DIRECTION_SOUTH;
  } else if (!strcmp(direction, "east")) {
    return HERO_DIRECTION_EAST;
  } else if (!strcmp(direction, "west")) {
    return HERO_DIRECTION_WEST;
  }

  return HERO_DIRECTION_NORTH;
}

void SGSHero::setAI(std::string& ai)
{
  HERO_AI hero_ai = HERO_AI_ATTACK;
  if (ai == "attack") {
    hero_ai = HERO_AI_ATTACK;
  } else if (ai == "defense") {
    hero_ai = HERO_AI_DEFENSE;
  } else if (ai == "stay") {
    hero_ai = HERO_AI_STAY;
  }
  setAI(hero_ai);
}


void SGSHero::setStatus(std::string& status)
{
  HERO_STATUS hero_status;
  if (status == "chaos") {
    hero_status = HERO_STATUS_CHAOS;
  }
  setStatus(hero_status);
}


void SGSHero::setStatus(HERO_STATUS status)
{
  __status = status;
  switch (status)
  {
  case HERO_STATUS_CHAOS: 
    {
      std::string chaos_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(SG_SKIRMISH_SCENE_HERO_STATUS_CHAOS);
      Sprite* chaos_sprite = Sprite::create(chaos_res_file_full_path);
      chaos_sprite->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
      chaos_sprite->setPosition(Vec2(SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT));
      this->addChild(chaos_sprite);
      break;
    }
  default:
    break;
  }
}

SGSPointList* SGSHero::getAttackArea()
{
  return getAttackAreaFromPosition(this->getMapPosition());
}

SGSPointList* SGSHero::getAttackAreaFromPosition(SGSPoint& pos)
{
  static SGSPointList point_list;

  SGSPointList::iterator iter;

  for (iter = point_list.begin(); iter != point_list.end();) {
    iter = point_list.erase(iter);
  }

  point_list.push_back(pos.getUp());
  point_list.push_back(pos.getDown());
  point_list.push_back(pos.getLeft());
  point_list.push_back(pos.getRight());

  return &point_list;
}

void  SGSHero::setActionFinishedCallback(const SGSHeroActionFinishedCallback& callback)
{
  SGSHero::__move_finished_callback = callback;
}

void SGSHero::setActive(bool active)
{
  __active = active;
  updataSprite();
}

void SGSHero::setDirection(HERO_DIRECTION direction)
{
  __direction = direction;
  switch (__direction)
  {
  case HERO_DIRECTION_EAST:
    setFlippedX(true);
    break;
  case HERO_DIRECTION_WEST:
  case HERO_DIRECTION_NORTH:
  case HERO_DIRECTION_SOUTH:
    setFlippedX(false);
    break;
  default:
    break;
  }

}


void SGSHero::updataSprite()
{
  faceTo(__direction);
  setColor(Color3B::WHITE);

  if (!__active) {
    stopAllActions();
    SpriteFrame* frame;
    switch (__direction)
    {
    case HERO_DIRECTION_SOUTH:
      frame = __sprite_frames.at(0);
      break;
    case HERO_DIRECTION_NORTH:
      frame = __sprite_frames.at(2);
      break;
    case HERO_DIRECTION_EAST:
    case HERO_DIRECTION_WEST:
      frame = __sprite_frames.at(4);
      break;
    default:
      break;
    }
    setSpriteFrame(frame);
    setColor(Color3B::GRAY);
  } 
}


