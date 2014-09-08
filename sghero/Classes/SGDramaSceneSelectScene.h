#ifndef SG_DRMAM_SCENE_SELECT_SCENE_H
#define SG_DRMAM_SCENE_SELECT_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

class SGDramaSceneSelectScene : public Layer
{
public:
  static Scene* creatScene(const char* hero_name, const char* content, int* ret_add);

  CREATE_FUNC(SGDramaSceneSelectScene);
  virtual bool init(); 
  
private:
  void menuItem1Callback(cocos2d::Ref* pSender);
  void menuItem2Callback(cocos2d::Ref* pSender);
  void menuItem3Callback(cocos2d::Ref* pSender);

  int* __ret;
};

#endif