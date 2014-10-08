#ifndef SG_SKIRMISH_OBJ_H
#define SG_SKIRMISH_OBJ_H

#include "cocos2d.h"
#include "SGObserver.h"
#include "SGSPoint.h"
USING_NS_CC;


class SGSkirmishObj : public Sprite , public SGObservable
{
public:
  static SGSkirmishObj* create(const char* name, SGObserver* observer);
  explicit SGSkirmishObj(SGObserver* observer) : SGObservable(observer) {}

  virtual bool init(const char* name);
  virtual void setMapPosition(SGSPoint& map_pos);
  void setMapPosition(Vec2& pos);
  SGSPoint& getMapPosition() { return __map_position; }
protected:
  SGSPoint __map_position;
};

#endif