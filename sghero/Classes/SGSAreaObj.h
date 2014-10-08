#ifndef SG_SKIRMISH_AREA_OBJ_H
#define SG_SKIRMISH_AREA_OBJ_H

#include "SGSObj.h"

class SGSAreaObj :public SGSObj 
{
public:
  static SGSAreaObj* create(std::string& name);
  SGSAreaObj(const char* name) : SGSObj(NULL) {}
  virtual bool init(std::string& name);

};



#endif