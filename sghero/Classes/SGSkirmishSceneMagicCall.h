#ifndef SG_SKIRMISH_SCENE_MAGIC_CALL
#define SG_SKIRMISH_SCENE_MAGIC_CALL

#include "cocos2d.h"
USING_NS_CC;

class SGSkirmishSceneMagicCall : public Layer 
{
public:
  static Scene* createScene(std::string& magic, Vec2& pos);

  static SGSkirmishSceneMagicCall* create(std::string& magic, Vec2& pos);
  bool init(std::string& magic, Vec2& pos);

  void actionFinished();
};

#endif