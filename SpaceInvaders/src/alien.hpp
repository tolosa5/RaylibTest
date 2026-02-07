#pragma once
#include "raylib.h"
#include "renderable.hpp"
#include "Event.hpp"
#include "laser.hpp"

class Alien: public Renderable
{
    public:
        Alien(Vector2 position, int type);

        void Update();
        void Draw() override;
        int GetType() { return type; }
        static void UnloadAlienTextures();
        void ChangeDirection();
        void MoveDown(int distance) { position.y += distance; }
        void AlienShoot();

        Event<Laser> OnRayShot;

        int type;
        static Texture2D alienImages[3];
        static int aliensMoveDirection;
};