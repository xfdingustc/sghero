#ifndef SG_SKIRMISH_SCENE_MAGIC_CALL
#define SG_SKIRMISH_SCENE_MAGIC_CALL

#include "cocos2d.h"
USING_NS_CC;

class SGSMagicCall : public Layer 
{
public:
  static Scene* createScene(std::string& magic, Vec2& pos);

  static SGSMagicCall* create(std::string& magic, Vec2& pos);
  bool init(std::string& magic, Vec2& pos);

  void actionFinished();
};

#endif