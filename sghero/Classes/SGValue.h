#ifndef SG_VALUE_H
#define SG_VALUE_H

#include "cocos2d.h"
USING_NS_CC;

class SGValue {
public:
  explicit SGValue();
  ~SGValue();

  SGValue& operator=(const SGValue& val);

  typedef enum {
    SG_TYPE_NONE = 0,
    SG_TYPE_CHAR,
    SG_TYPE_INT16,
    SG_TYPE_UINT16,
    SG_TYPE_INT32,
    SG_TYPE_UINT32,
    SG_TYPE_INT64,
    SG_TYPE_UINT64,
    SG_TYPE_FLOAT,
    SG_TYPE_PTR,
    SG_TYPE_BOOL,
  } SGValueType;
  void setData(SGValueType type, const void* data, unsigned int size);
  void getData(SGValueType* type, const void** data, unsigned int* size);
private:
  SGValueType __type;
  void* __data;
  unsigned int __size;

};


#endif