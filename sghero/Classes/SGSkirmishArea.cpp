#include "SGSkirmishArea.h"
#include "SGSkirmishAreaObj.h"

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
    SGSkirmishAreaObj* obj = SGSkirmishAreaObj::create("path");
    obj->setMapPosition(pos);
    this->addChild(obj);

  }
}
