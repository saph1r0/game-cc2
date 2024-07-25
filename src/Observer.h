#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer() {}
    virtual void itemCounter(int item) = 0;
    virtual void collisionCounter(int collision) = 0;
    virtual void healthCounter(int health) = 0;
};

#endif