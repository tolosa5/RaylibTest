#include "Headers/block.hpp"

Block::Block(Vector2 position)
{
    this->position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, Utils::YellowColor());
}

Rectangle Block::GetCollider()
{
    return {position.x, position.y, (float)size, (float)size};
}
