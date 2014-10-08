#include "SGSkirmishArea.h"
#include "SGSkirmishAreaObj.h"

SGSkirmishArea* SGSkirmishArea::create(std::string& name)
{
  SGSkirmishArea* area = new SGSkirmishArea;
  if (area && area->init()) {
    area->__name = name;
    area->autorelease();
    return area;
  } else {
    delete area;
    return NULL;
  }
  
}
SGSkirmishArea* SGSkirmishArea::create(std::string& name, SGSPointList& point_list)
{
  SGSkirmishArea* area = new SGSkirmishArea;
  if (area && area->initWithPointList(point_list)) {
    area->__name = name;
    area->autorelease();
    return area;
  } else {
    delete area;
    return NULL;
  }
}

 SGSkirmishArea::~SGSkirmishArea()
 {
 }


bool SGSkirmishArea::init()
{
  if (!Layer::init()) {
    return false;
  }
  return true;
}

bool SGSkirmishArea::initWithPointList(SGSPointList& point_list)
{
  SGSPointList::iterator iter;
  for (iter = point_list.begin(); iter != point_list.end(); iter++) {
    addOnePoint(*iter);
  }
  return init();
}


void SGSkirmishArea::addOnePoint(SGSPoint& pos)
{
  __point_list.push_back(pos);
}

bool SGSkirmishArea::containPoint(Vec2& pos)
{
  SGSPointList::iterator iter;

  for (iter = __point_list.begin(); iter != __point_list.end(); iter++) {
    SGSPoint map_pos = *iter;
    if (map_pos == SGSPoint::openGLPos2MapPos(pos)) {
      return true;
    }
  }
  return false;
}
void SGSkirmishArea::show()
{
  SGSPointList::iterator iter;
  for (iter = __point_list.begin(); iter != __point_list.end(); iter++) {
    SGSPoint pos = *iter;
    SGSkirmishAreaObj* obj = SGSkirmishAreaObj::create(__name);
    obj->setMapPosition(pos);
    this->addChild(obj);

  }
}
