#include "SGGlobalSettings.h"
#include "SGSkirmishAreaObj.h"


SGSkirmishAreaObj* SGSkirmishAreaObj::create(const char* name)
{
  SGSkirmishAreaObj* obj = new SGSkirmishAreaObj(NULL);
  if (obj && obj->init(name)) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return NULL;
  }
}


bool SGSkirmishAreaObj::init(const char* name)
{
  std::string res_name = SG_SKIRMISH_SCENE_OBJ_RES_PATH;
  res_name.append(name);
  res_name.append(".png");

  if (!Sprite::initWithFile(FileUtils::getInstance()->fullPathForFilename(res_name))) {
    return false;
  }
  setName(name);
  this->setOpacity(100);

}