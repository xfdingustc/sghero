#ifndef SG_DRAMA_SCENE_H
#define SG_DRAMA_SCENE_H
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
USING_NS_CC;


class SGDramaScene : public Layer
{
public:
  static cocos2d::Scene* createScene();
   

  CREATE_FUNC(SGDramaScene);
  virtual bool init(); 

private:
  bool parseDramaSceneXmlFile(const char* file);
  bool parseDrameSceneEvents(tinyxml2::XMLElement* event);
};

#endif