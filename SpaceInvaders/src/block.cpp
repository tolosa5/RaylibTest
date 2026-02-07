#include "block.hpp"

Block::Block(Vector2 position)
{
    this->position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, Utils::YellowColor());
}

Rectangle Block::GetCollisionBox()
{
    return {position.x, position.y, size, size};
}
