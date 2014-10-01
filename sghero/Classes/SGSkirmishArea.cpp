#include "SGSkirmishArea.h"
#include "SGSkirmishAreaObj.h"

void SGSkirmishArea::addOnePoint(SGSkirmishMapPos& pos)
{
  __point_list.push_back(pos);
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
