#include "SGSObj.h"
#include "SGGlobalSettings.h"

SGSObj* SGSObj::create(const char* name, SGObserver* observer)
{
  SGSObj* obj = new SGSObj(observer);
  if (obj && obj->init(name)) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return NULL;
  }
}

bool SGSObj::init(const char* name)
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


void SGSObj::setMapPosition(SGSPoint& map_pos) 
{ 
  Vec2 pos = SGSPoint::mapPos2OpenGLPos(map_pos);
  
  setPosition(pos);
  
}
void SGSObj::setMapPosition(Vec2& pos)
{
  SGSPoint map_pos = SGSPoint::openGLPos2MapPos(pos);
  setMapPosition(map_pos);
}


