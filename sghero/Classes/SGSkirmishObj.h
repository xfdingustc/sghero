#ifndef SG_SKIRMISH_OBJ_H
#define SG_SKIRMISH_OBJ_H

#include "cocos2d.h"
#include "SGObserver.h"
USING_NS_CC;


class SGSkirmishObj : public Sprite , public SGObservable
{
public:
  static SGSkirmishObj* create(const char* name);
  virtual bool init(const char* name);
  void setMapPosition(Vec2& map_pos);
  Vec2& getMapPosition() { return __map_position; }
protected:
  Vec2 __map_position;
  Vec2& mapPos2OpenGLPos(Vec2& origin);
  
};

#endif