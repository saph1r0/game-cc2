#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "Player.h"

class Subject {
private:
    std::vector<Observer*> observers;
    int item;
    int collision;

public:
    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);
    void notifyObservers();

    void setItem(int a);

    void setCollision(int b);

    void addItem();

    void addNitem();

    void addCollision();

    int getItem() const;

    int getCollision() const;
};

#endif
