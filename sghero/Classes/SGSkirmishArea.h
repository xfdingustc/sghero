#ifndef SG_SKIRMISH_AREA_H
#define SG_SKIRMISH_AREA_H

#include "cocos2d.h"
#include "SGSkirmishMapPos.h"
USING_NS_CC;

class SGSkirmishArea : public Layer
{
public:
  CREATE_FUNC(SGSkirmishArea);
  bool init() { return true;};
  bool containPoint(Vec2& pos);
  void addOnePoint(SGSkirmishMapPos& pos);
  void show();
private:
  typedef std::vector<SGSkirmishMapPos> SGSkirmishPointList;
  SGSkirmishPointList  __point_list;
};
#endif