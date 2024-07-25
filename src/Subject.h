#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Observer.h"

class Subject {
private:
    std::vector<Observer*> observers; //vector that allows you to enter any type of class thanks to observer.h
    int item;
    int collision;
    int health; //3 variables we track

public:
    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);
    void notifyObservers();
    void notifyObservers2();

    void setItem(int a);

    void setCollision(int b);

    void setHealth(int c);

    void addItem();

    void addCollision();

    void removeHealth();


    int getItem() const;

    int getCollision() const;

    int getHealth() const;
};

#endif
