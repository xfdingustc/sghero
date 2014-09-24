#ifndef SG_OBSERVER_H
#define SG_OBSERVER_H

class SGObserver
{
public:
  virtual void notify() {} ;
};

class SGObservable {
public:
  void setObserver(SGObserver* observer) { __observer = observer; }
protected:
  void notifyObserver() { __observer->notify(); }
private:
  SGObserver* __observer;
};

#endif // !SG_OBSERVER_H

