#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, Vector4 collision) : BaseCharacter(collision)
{
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    worldPos = pos;
    width = texture.width / frameCount;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::update(float dt)
{
    if (!getAlive())
        return;
    Vector2 targetPos = Vector2Add(target->getWorldPos(), target->getScreenPos());
    if (Vector2Length(velocity) < radius)
        velocity = {};
    else
    {
        velocity = Vector2Subtract(targetPos, worldPos);
        velocity = Vector2Normalize(velocity);
    }
    velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(targetPos, worldPos)), speed);
    BaseCharacter::update(dt);
    if (CheckCollisionRecs(getCollisionRectangle(), target->getCollisionRectangle()))
    {
        target->takeDamage(damage * dt);
    }
}

Vector2 Enemy::getScreenPos() const
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
