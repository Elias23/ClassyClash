#include "Character.h"
#include "rayMath.h"

Character::Character(Vector2 winSize)
{
    screenPos = Vector2{
        winSize.x / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        winSize.y / 2.0f - 4.0f * (0.5f * (float)texture.height)};
    width = texture.width / frameCount;
    height = texture.height;
};

void Character::update(float dt)
{
    Vector2 direction{0, 0};
    direction.x = 0;
    direction.y = 0;
    worldPosLastFrame = worldPos;

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
    runningTime += dt;
    if (runningTime > frameTime)
    {
        currentFrame++;
        runningTime = 0;
        if (currentFrame > frameCount)
            currentFrame = 0;
    }
}

void Character::draw()
{
    // Draw Knight
    Rectangle source{currentFrame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}