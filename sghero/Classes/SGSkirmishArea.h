#ifndef SG_SKIRMISH_AREA_H
#define SG_SKIRMISH_AREA_H

#include "cocos2d.h"
USING_NS_CC;

class SGSkirmishArea : public Layer
{
public:
  CREATE_FUNC(SGSkirmishArea);
  bool init() { return true;};
  
private:
  typedef std::vector<Vec2> SGSkirmishPointList;
  SGSkirmishPointList  __point_list;
};
#endif