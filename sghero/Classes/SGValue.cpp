extern "C" {
//#include "stdio.h"
//#include "stdlib.h"
}
#include "SGValue.h"

SGValue::SGValue() 
  : __type(SG_TYPE_NONE),
    __data(NULL),
    __size(0) 
{

}


SGValue::~SGValue() 
{
  if (__data) {
    free(__data);
    __data = NULL;
    __size = 0;
  }
}


SGValue& SGValue::operator=(const SGValue& val) 
{
  __type = val.__type;

  if (__data) {
    free(__data);
    __data = NULL;
  }

  __data = malloc(val.__size);
  if (__data) {
    memcpy(__data, val.__data, val.__size);
  }
  __size = val.__size;

  return *this;
}

void SGValue::setData(SGValueType type, const void* data, unsigned int size)
{
  __type = type;
  if (__data) {
    free(__data);
    __data = NULL;
  }

  __data = malloc(size);
  memcpy(__data, data, size);
  __size = size;
}


void SGValue::getData(SGValueType* type, const void** data, unsigned int* size) {
  *type = __type;
  *size = __size;
  *data = __data;
}