#ifndef SG_SKIRMISH_AREA_H
#define SG_SKIRMISH_AREA_H

#include "cocos2d.h"
#include "SGSkirmishMapPos.h"
USING_NS_CC;

class SGSkirmishArea : public Layer
{
  friend class SGSkirmishTerrain;
public:
  static SGSkirmishArea*  create(std::string& name);
  static SGSkirmishArea*  create(std::string& name, SGSkirmishPointList& point_list);

  virtual ~SGSkirmishArea();

  void                    addOnePoint(SGSkirmishMapPos& pos);
  bool                    containPoint(Vec2& pos);
  bool                    init();
  bool                    initWithPointList(SGSkirmishPointList& point_list);
  void                    show();
private:
  SGSkirmishPointList               __point_list;
  std::string             __name;
};
#endif