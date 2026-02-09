#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>

using namespace std;

template <typename T>
class Event
{
public:
    using Callback = function<void(T)>;

    void Subscribe(const Callback& callback)
    {
        listeners.push_back(callback);
    }

    void Invoke(T arg)
    {
        for (auto& callback : listeners)
        {
            callback(arg);
        }
    }

private:
    vector<Callback> listeners;
};

#endif