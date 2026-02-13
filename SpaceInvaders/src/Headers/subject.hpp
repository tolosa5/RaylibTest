#include <vector>

class Observer;

class Subject
{
    virtual void RegisterObserver(Observer* observer) = 0;
    virtual void RemoveObserver(Observer* observer) = 0;
    virtual void NotifyObservers() = 0;
    virtual ~Subject() {}
};