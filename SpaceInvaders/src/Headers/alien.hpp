#pragma once
#include "raylib.h"
#include "Event.hpp"
#include "laser.hpp"
#include "physicObject.hpp"

class Alien: public PhysicObject
{
    public:
        Alien(Vector2 position, int type);

        void Update(float dt);
        void Draw() override;
        Rectangle GetCollider() override;
        int GetType() { return type; }
        static void UnloadAlienTextures();
        void ChangeDirection();
        void MoveDown(int distance) { position.y += distance; }
        void AlienShoot();

        Event<Laser> OnLaserShot;

        int type;
        int value;
        static Texture2D alienImages[3];
        static int aliensMoveDirection;
};