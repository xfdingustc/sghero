#include "SGObserver.h"


SGObserver::~SGObserver()
{
}


void SGObservable::addObserver(SGObserver* observer)
{
  if (!observer) {
    return;
  }
  std::vector<SGObserver*>::iterator iter;
  for (iter = __observers.begin(); iter != __observers.end(); iter++) {
    SGObserver* one_observer = *iter;
    // already have this observer
    if (one_observer == observer) {
      return;
    }
  }
  __observers.push_back(observer);
}

void SGObservable::removeObserver(SGObserver* observer)
{
  std::vector<SGObserver*>::iterator iter;
  for (iter = __observers.begin(); iter != __observers.end(); iter++) {
    SGObserver* one_observer = *iter;
    // already have this observer
    if (one_observer == observer) {
      __observers.erase(iter);
      return;
    }
  }
  
}


void SGObservable::notifyObserver() { 
  std::vector<SGObserver*>::iterator iter;
  for (iter = __observers.begin(); iter != __observers.end(); iter++) {
    SGObserver* one_observer = *iter;
    one_observer->notify();
  }
}

void SGObservable::notifyObserver(const char* reason, void* ptr) { 
  std::vector<SGObserver*>::iterator iter;
  for (iter = __observers.begin(); iter != __observers.end(); iter++) {
    SGObserver* one_observer = *iter;
    one_observer->notify(reason, ptr);
  }
}