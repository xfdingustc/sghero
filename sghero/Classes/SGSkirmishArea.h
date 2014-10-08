#ifndef SG_SKIRMISH_AREA_H
#define SG_SKIRMISH_AREA_H

#include "cocos2d.h"
#include "SGSPoint.h"
USING_NS_CC;

class SGSkirmishArea : public Layer
{
  friend class SGSTerrain;
public:
  static SGSkirmishArea*  create(std::string& name);
  static SGSkirmishArea*  create(std::string& name, SGSPointList& point_list);

  virtual ~SGSkirmishArea();

  void                    addOnePoint(SGSPoint& pos);
  bool                    containPoint(Vec2& pos);
  bool                    init();
  bool                    initWithPointList(SGSPointList& point_list);
  void                    show();
private:
  SGSPointList               __point_list;
  std::string             __name;
};
#endif