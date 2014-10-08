#include "SGSArea.h"
#include "SGSAreaObj.h"

SGSArea* SGSArea::create(std::string& name)
{
  SGSArea* area = new SGSArea;
  if (area && area->init()) {
    area->__name = name;
    area->autorelease();
    return area;
  } else {
    delete area;
    return NULL;
  }
  
}
SGSArea* SGSArea::create(std::string& name, SGSPointList& point_list)
{
  SGSArea* area = new SGSArea;
  if (area && area->initWithPointList(point_list)) {
    area->__name = name;
    area->autorelease();
    return area;
  } else {
    delete area;
    return NULL;
  }
}

 SGSArea::~SGSArea()
 {
 }


bool SGSArea::init()
{
  if (!Layer::init()) {
    return false;
  }
  return true;
}

bool SGSArea::initWithPointList(SGSPointList& point_list)
{
  SGSPointList::iterator iter;
  for (iter = point_list.begin(); iter != point_list.end(); iter++) {
    addOnePoint(*iter);
  }
  return init();
}


void SGSArea::addOnePoint(SGSPoint& pos)
{
  __point_list.push_back(pos);
}

bool SGSArea::containPoint(Vec2& pos)
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
void SGSArea::show()
{
  SGSPointList::iterator iter;
  for (iter = __point_list.begin(); iter != __point_list.end(); iter++) {
    SGSPoint pos = *iter;
    SGSAreaObj* obj = SGSAreaObj::create(__name);
    obj->setMapPosition(pos);
    this->addChild(obj);

  }
}
