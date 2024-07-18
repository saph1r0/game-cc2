#include "Subject.h"

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

    void Subject::addItem() {
        item++;
        notifyObservers();
    }

    void Subject::addCollision() {
        collision++;
        notifyObservers();
    }

    int Subject::getItem() const {
        return item;
    }

    int Subject::getCollision() const {
        return collision;
    }
