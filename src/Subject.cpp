#include <iostream>
#include <algorithm>
#include "Subject.h"
#include "Observer.h"

//we add an observer to the observers array. 
    void Subject::addObserver(Observer* observer) {
        observers.push_back(observer);
    }
//delete observer
    void Subject::removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
//""notifies"" all the observer of the class - calls the overloaded functions in the object to make an update
    void Subject::notifyObservers() {
        for (Observer* observer : observers) {
            observer->itemCounter(item);
            observer->collisionCounter(collision);
            observer->healthCounter(health);
        }
    }
    /*
    void Subject::notifyObservers2() {
        for (Observer* observer : observers) {
            observer->collisionCounter(collision);
        }
    }
*/
//enter the desired quantity of the variable
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

//is added when the function is called
    void Subject::addItem() {
        item++;
        notifyObservers();
    }

    void Subject::addCollision() {
        collision++;
        notifyObservers();
    }
//in the case of helth it decreases
    void Subject::removeHealth() {
        health--;
        notifyObservers();
    }
//get functions to obtain the variables
    int Subject::getItem() const {
        return item;
    }

    int Subject::getCollision() const {
        return collision;
    }

    int Subject::getHealth() const {
        return health;
    }
