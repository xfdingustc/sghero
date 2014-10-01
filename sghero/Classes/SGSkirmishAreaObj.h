#ifndef SG_SKIRMISH_AREA_OBJ_H
#define SG_SKIRMISH_AREA_OBJ_H

#include "SGSkirmishObj.h"

class SGSkirmishAreaObj :public SGSkirmishObj 
{
public:
  static SGSkirmishAreaObj* create(const char* name);
  SGSkirmishAreaObj(const char* name) : SGSkirmishObj(NULL) {}
  virtual bool init(const char* name);

};



#endif