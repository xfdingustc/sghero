#ifndef SG_SKIRMISH_AREA_H
#define SG_SKIRMISH_AREA_H

#include "cocos2d.h"
#include "SGSkirmishMapPos.h"
USING_NS_CC;

class SGSkirmishArea : public Layer
{
  friend class SGSkirmishTerrain;
public:
  typedef SGSkirmishMapPos::SGSkirmishPointList PointList;

  static SGSkirmishArea*  create(std::string& name);
  static SGSkirmishArea*  create(std::string& name, PointList& point_list);

  void                    addOnePoint(SGSkirmishMapPos& pos);
  bool                    containPoint(Vec2& pos);
  bool                    init();
  bool                    initWithPointList(PointList& point_list);
  void                    show();
private:
  PointList               __point_list;
  std::string             __name;
};
#endif