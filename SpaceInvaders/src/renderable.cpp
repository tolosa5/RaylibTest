#include "Headers/renderable.hpp"

Renderable::Renderable()
{
    
}

void Renderable::Draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
}