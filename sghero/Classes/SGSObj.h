#ifndef SG_SKIRMISH_OBJ_H
#define SG_SKIRMISH_OBJ_H

#include "cocos2d.h"
#include "SGObserver.h"
#include "SGSPoint.h"
USING_NS_CC;


class SGSObj : public Sprite , public SGObservable
{
public:
  static SGSObj* create(const char* name, SGObserver* observer);
  explicit SGSObj(SGObserver* observer)  { addObserver(observer); }

  virtual bool init(const char* name);
  virtual void setMapPosition(SGSPoint& map_pos);
  void setMapPosition(Vec2& pos);
  SGSPoint getMapPosition() { 
    Vec2 pos = getPosition();
    return SGSPoint::openGLPos2MapPos(pos); 
  }
protected:
};

#endif