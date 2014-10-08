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
SGSkirmishArea* SGSkirmishArea::create(std::string& name, SGSkirmishPointList& point_list)
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

bool SGSkirmishArea::initWithPointList(SGSkirmishPointList& point_list)
{
  SGSkirmishPointList::iterator iter;
  for (iter = point_list.begin(); iter != point_list.end(); iter++) {
    addOnePoint(*iter);
  }
  return init();
}


void SGSkirmishArea::addOnePoint(SGSkirmishMapPos& pos)
{
  __point_list.push_back(pos);
}

bool SGSkirmishArea::containPoint(Vec2& pos)
{
  SGSkirmishPointList::iterator iter;

  for (iter = __point_list.begin(); iter != __point_list.end(); iter++) {
    SGSkirmishMapPos map_pos = *iter;
    if (map_pos == SGSkirmishMapPos::openGLPos2MapPos(pos)) {
      return true;
    }
  }
  return false;
}
void SGSkirmishArea::show()
{
  SGSkirmishPointList::iterator iter;
  for (iter = __point_list.begin(); iter != __point_list.end(); iter++) {
    SGSkirmishMapPos pos = *iter;
    SGSkirmishAreaObj* obj = SGSkirmishAreaObj::create(__name);
    obj->setMapPosition(pos);
    this->addChild(obj);

  }
}
