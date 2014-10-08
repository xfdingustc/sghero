#ifndef SG_SKIRMISH_POINT_H
#define SG_SKIRMISH_POINT_H

#include "cocos2d.h"
USING_NS_CC;

#include "SGGlobalSettings.h"
class SGSPoint 
{
public:
  int x;
  int y;
  SGSPoint() : x(0), y(0) {}
  SGSPoint(int _x, int _y) : x(_x), y(_y) {}

  inline bool operator==(const SGSPoint& v) const {
    return x==v.x && y==v.y;
  };

  inline bool operator!=(const SGSPoint& v) const {
    return x!=v.x || y!=v.y;
  };
  inline static Vec2 mapPos2OpenGLPos(SGSPoint& origin) {
    Vec2 new_pos;

    Size size = Director::getInstance()->getVisibleSize();

    new_pos.x = (origin.x + 0.5f) * SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH ;
    new_pos.y = size.height - (origin.y + 0.5f) * SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT;
    return new_pos;

  }

  inline static SGSPoint openGLPos2MapPos(Vec2& origin)
  {
    SGSPoint map_pos;

    Size size = Director::getInstance()->getVisibleSize();
    map_pos.x = origin.x / SG_SKIRMISH_SCENE_HERO_WALK_RES_WIDTH;
    map_pos.y = (size.height - origin.y) / SG_SKIRMISH_SCENE_HERO_WALK_RES_HEIGHT;
    return map_pos;
  }

  inline SGSPoint getUp() {
    SGSPoint up;
    up.x = x;
    up.y = y-1;
    return up;
  }

  inline SGSPoint getDown() {
    SGSPoint down;
    down.x = x;
    down.y = y+1;
    return down;
  }
  inline SGSPoint getLeft() {
    SGSPoint left;
    left.x = x-1;
    left.y = y;
    return left;
  }
  inline SGSPoint getRight() {
    SGSPoint right;
    right.x = x+1;
    right.y = y;
    return right;
  }

};
typedef std::vector<SGSPoint> SGSPointList;

#endif