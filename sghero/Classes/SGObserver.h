#ifndef SG_OBSERVER_H
#define SG_OBSERVER_H
#include "cocos2d.h"
USING_NS_CC;

class SGObservable;
class SGObserver
{
  friend class SGObservable;
public:
  virtual ~SGObserver();
  virtual void notify() {} 
  virtual void notify(const char* reason, void* ptr) {}
private:
  std::vector<SGObservable*> __observables;
};

class SGObservable {
public:
  //SGObservable() : __observer(NULL) {}
  //SGObservable(SGObserver* observer) : __observer(observer) {}
  void addObserver(SGObserver* observer); 
  void removeObserver(SGObserver* observer);
protected:
  void notifyObserver();

  void notifyObserver(const char* reason, void* ptr);
private:
  std::vector<SGObserver*> __observers;
};

#endif // !SG_OBSERVER_H

