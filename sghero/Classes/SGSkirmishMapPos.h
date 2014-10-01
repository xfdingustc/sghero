#ifndef SG_SKIRMISH_MAP_POS_H
#define SG_SKIRMISH_MAP_POS_H

class SGSkirmishMapPos 
{
public:
  int x;
  int y;
  SGSkirmishMapPos() : x(0), y(0) {}
  SGSkirmishMapPos(int _x, int _y) : x(_x), y(_y) {}

  inline bool operator==(const SGSkirmishMapPos& v) const {
    return x==v.x && y==v.y;
  };

  inline bool operator!=(const SGSkirmishMapPos& v) const {
    return x!=v.x || y!=v.y;
  };

};

#endif