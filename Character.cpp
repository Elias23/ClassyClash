#include "Character.h"
#include "rayMath.h"

Character::Character(Vector2 winSize)
{
    screenPos = Vector2{
        winSize.x / 2.0f - scale * (0.5f * static_cast<float>(texture.width) / 6.0f),
        winSize.y / 2.0f - scale * (0.5f * static_cast<float>(texture.height))};
    width = texture.width / frameCount;
    height = texture.height;
};

void Character::update(float dt)
{
    BaseCharacter::update(dt);
    Vector2 direction{0, 0};
    direction.x = 0;
    direction.y = 0;
    if (IsKeyDown(KEY_A))
        direction.x -= 1;
    if (IsKeyDown(KEY_D))
        direction.x += 1;
    if (IsKeyDown(KEY_W))
        direction.y -= 1;
    if (IsKeyDown(KEY_S))
        direction.y += 1;
    if (Vector2Length(direction) > 0)
    {
        texture = run;
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    }
    else
    {
        texture = idle;
    }
}