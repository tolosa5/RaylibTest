#pragma once

#include "subject.hpp"
#include <iostream>
#include <algorithm>

class HudManager : public Subject
{
public:

    HudManager();
    ~HudManager();
    
    void RegisterObserver(Observer* observer) override;
    void RemoveObserver(Observer* observer) override;
    void NotifyObservers() override;

    void SetLifes(int lifes);
    void SetPoints(int points);

private:
    std::vector<Observer*> observers;
};