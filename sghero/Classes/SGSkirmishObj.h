#ifndef SG_SKIRMISH_OBJ_H
#define SG_SKIRMISH_OBJ_H

#include "cocos2d.h"
#include "SGObserver.h"
#include "SGSkirmishMapPos.h"
USING_NS_CC;


class SGSkirmishObj : public Sprite , public SGObservable
{
public:
  static SGSkirmishObj* create(const char* name, SGObserver* observer);
  explicit SGSkirmishObj(SGObserver* observer) : SGObservable(observer) {}

  virtual bool init(const char* name);
  void setMapPosition(SGSkirmishMapPos& map_pos);
  void setMapPosition(Vec2& pos);
  SGSkirmishMapPos& getMapPosition() { return __map_position; }
protected:
  SGSkirmishMapPos __map_position;
};

#endif