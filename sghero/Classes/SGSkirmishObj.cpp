#include "SGSkirmishObj.h"
#include "SGGlobalSettings.h"

SGSkirmishObj* SGSkirmishObj::create(const char* name, SGObserver* observer)
{
  SGSkirmishObj* obj = new SGSkirmishObj(observer);
  if (obj && obj->init(name)) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return NULL;
  }
}

bool SGSkirmishObj::init(const char* name)
{
  if (!Sprite::init()) {
    return false;
  }
  
  setName(name);
  notifyObserver("object_add", (void*)this);
  // init image
  Vector<SpriteFrame*>* animFrames = new Vector<SpriteFrame*>;

  for (int i = 0; i < 4; i++) {
    std::string res_name = SG_SKIRMISH_SCENE_OBJ_RES_PATH;
    res_name.append(name);
    char index[10];
    sprintf(index, "-%d", i+1);
    res_name.append(index);
    res_name.append(".png");
    std::string obj_res_file_full_path = FileUtils::getInstance()->fullPathForFilename(res_name);
    SpriteFrame* frame = SpriteFrame::create(obj_res_file_full_path, 
        Rect(0, 0, SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH, SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH));
    animFrames->pushBack(frame);
   
  }
  Animation* animation = Animation::createWithSpriteFrames(*animFrames, 0.5f);
  Animate* animate = Animate::create(animation);
  animate->retain();
  RepeatForever* repeat_animate = RepeatForever::create(animate);
  this->runAction(repeat_animate);
  return true;
}


void SGSkirmishObj::setMapPosition(Vec2& map_pos) 
{ 
  __map_position = map_pos; 
  Vec2 pos = mapPos2OpenGLPos(__map_position);
  
  setPosition(pos);
  
}

Vec2& SGSkirmishObj::mapPos2OpenGLPos(Vec2& origin)
{
  Vec2 new_pos;

  Size size = Director::getInstance()->getVisibleSize();

  new_pos.x = (origin.x + 0.5f) * SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH ;
  new_pos.y = size.height - (origin.y + 0.5f) * SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT;
  return new_pos;
}