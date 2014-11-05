#include "SGMessage.h"

SGMessage::SGMessage(unsigned int what, SGMessageHandler* handle)
  : __what(what),
    __handler(handle)
{

}

SGMessage::~SGMessage()
{
  cleanItems();
}

bool SGMessage::cleanItems()
{
  std::map<SGHash, SGValue*>::iterator it;
  for (it = __items.begin(); it != __items.end(); it++) {
    delete it->second;
  }
  __items.clear();

  return true;
}

void SGMessage::setWhat(unsigned int what)
{
  __what = what;
}


unsigned int SGMessage::what() const {
  return __what;
}


void SGMessage::setInt(const char* name, int value)
{
  SGHash name_hash = getHashFromString(name);

  SGValue* new_value = new SGValue();
  new_value->setData(SGValue::SG_TYPE_INT32, &value, sizeof(value));

  __items.insert(std::pair<SGHash, SGValue*>(name_hash, new_value));

}


void SGMessage::setPtr(const char* name, void *value) {
  SGHash field_hash = getHashFromString(name);

  SGValue* new_value = new SGValue;
  new_value->setData(SGValue::SG_TYPE_PTR, &value, sizeof(value));

  __items.insert(std::pair<SGHash, SGValue*>(field_hash, new_value));
}


 bool SGMessage::getInt(const char* name, int* value)
 {
   SGHash field_hash = getHashFromString(name);

   std::map<SGHash, SGValue*>::iterator it;

   it = __items.find(field_hash);
   if (it == __items.end()) {
     return false;
   }

   SGValue* found_value = it->second;

   unsigned int size = 0;
   const void* data;
   SGValue::SGValueType type;

   found_value->getData(&type, &data, &size);
   if (type != SGValue::SG_TYPE_INT32) {
     return false;
   }
   

   *value = *((unsigned int*)(data));

   return true;
 }


 bool SGMessage::getPtr(const char* name, void **value) {
   SGHash field_hash = getHashFromString(name);

   std::map<SGHash, SGValue*>::iterator it;

   it = __items.find(field_hash);
   if (it == __items.end()) {
     return false;
   }

   SGValue* found_value = it->second;

   unsigned int datasize = 0;
   const void* data;
   SGValue::SGValueType type;

   found_value->getData(&type, &data, &datasize);
   if (type != SGValue::SG_TYPE_PTR) {
     return false;
   }
   if (datasize != sizeof(*value)) {
     return false;
   }

   *value = *(void **)data;

   return true;
 }



 void SGMessage::post()
 {
   __handler->postMessage(this);
 }