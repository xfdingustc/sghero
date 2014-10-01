#ifndef SG_OBSERVER_H
#define SG_OBSERVER_H

class SGObserver
{
public:
  virtual void notify() {} 
  virtual void notify(const char* reason, void* ptr) {}
};

class SGObservable {
public:
  SGObservable() : __observer(NULL) {}
  SGObservable(SGObserver* observer) : __observer(observer) {}
  void setObserver(SGObserver* observer) { __observer = observer; }
protected:
  void notifyObserver() { 
    if (__observer) { 
      __observer->notify(); 
    } 
  }

  void notifyObserver(const char* reason, void* ptr) { 
    if (__observer) {
      __observer->notify(reason, ptr); 
    }
  }
private:
  SGObserver* __observer;
};

#endif // !SG_OBSERVER_H

