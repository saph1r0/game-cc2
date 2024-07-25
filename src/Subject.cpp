#include <iostream>
#include <algorithm>
#include "Subject.h"
#include "Observer.h"


    void Subject::addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void Subject::removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void Subject::notifyObservers() {
        for (Observer* observer : observers) {
            observer->itemCounter(item);
            observer->collisionCounter(collision);
            observer->healthCounter(health);
        }
    }
    void Subject::notifyObservers2() {
        for (Observer* observer : observers) {
            observer->collisionCounter(collision);
        }
    }

    void Subject::setItem(int a) {
        item = a;
        notifyObservers();
    }

    void Subject::setCollision(int b) {
        collision = b;
        notifyObservers();
    }
    void Subject::setHealth(int c) {
        health = c;
        notifyObservers();
    }


    void Subject::addItem() {
        item++;
        notifyObservers();
    }

    void Subject::addCollision() {
        collision++;
        notifyObservers();
    }

    void Subject::removeHealth() {
        health--;
        notifyObservers();
    }

    int Subject::getItem() const {
        return item;
    }

    int Subject::getCollision() const {
        return collision;
    }

    int Subject::getHealth() const {
        return health;
    }
