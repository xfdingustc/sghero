#ifndef SG_OBSERVER_H
#define SG_OBSERVER_H

class SGObservable;
class SGObserver
{
public:
  virtual void notify() {} 
  virtual void notify(SGObservable* object, const char* reason, void* ptr) {}
};

class SGObservable {
public:
  void setObserver(SGObserver* observer) { __observer = observer; }
protected:
  void notifyObserver() { __observer->notify(); }
  void notifyObserver(SGObservable* object, const char* reason, void* ptr) { __observer->notify(object, reason, ptr); }
private:
  SGObserver* __observer;
};

#endif // !SG_OBSERVER_H

