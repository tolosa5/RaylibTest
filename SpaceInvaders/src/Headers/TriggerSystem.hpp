#pragma once
#include "raylib.h"
#include "TriggerComponent.hpp"
#include "vector"

class TriggerSystem
{
public:
    static void Register(TriggerComponent* t)
    {
        triggers.push_back(t);
    }

    static void Update()
    {
        for(auto* a : triggers)
        {
            for(auto* b : triggers)
            {
                if (a == b)
                    continue;

                bool colliding = CheckCollisionRecs(
                    a->trigger.bounds,
                    b->trigger.bounds
                );
                
                auto& set = a->overlapping;

                if (colliding)
                {
                    if (!set.contains(b->listener))
                    {
                        set.insert(b->listener);
                        a->listener->OnTriggerEnter(b->listener);
                    }
                }
            }
        }
    }

private:
    static inline std::vector<TriggerComponent*> triggers;
};