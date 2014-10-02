#ifndef SG_SKIRMISH_AREA_H
#define SG_SKIRMISH_AREA_H

#include "cocos2d.h"
#include "SGSkirmishMapPos.h"
USING_NS_CC;

class SGSkirmishArea : public Layer
{
  friend class SGSkirmishTerrain;
public:
  static SGSkirmishArea* create(std::string& name);
  bool init();
  bool containPoint(Vec2& pos);
  void addOnePoint(SGSkirmishMapPos& pos);
  void show();
private:
  typedef std::vector<SGSkirmishMapPos> SGSkirmishPointList;
  SGSkirmishPointList  __point_list;
  std::string __name;
};
#endif