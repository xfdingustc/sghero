#include "SGGlobalSettings.h"
#include "SGSAreaObj.h"


SGSAreaObj* SGSAreaObj::create(std::string& name)
{
  SGSAreaObj* obj = new SGSAreaObj(NULL);
  if (obj && obj->init(name)) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return NULL;
  }
}


bool SGSAreaObj::init(std::string& name)
{
  std::string res_name = SG_SKIRMISH_SCENE_OBJ_RES_PATH;
  res_name.append(name);
  res_name.append(".png");

  if (!Sprite::initWithFile(FileUtils::getInstance()->fullPathForFilename(res_name))) {
    return false;
  }
  setName(name);
  this->setOpacity(100);
  return true;
}