#include "BaseCharacter.h"
#include "raymath.h"
#include "main.h"

BaseCharacter::BaseCharacter(Vector4 collision) : collisionOffset(collision)
{
}

void BaseCharacter::draw()
{
    if (!getAlive())
        return;
    // Draw the character
    Rectangle source{currentFrame * width, 0.0f, rightLeft * width, height};
    Vector2 screenPos = getScreenPos();
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    if (DEBUG_MODE)
        DrawRectangleLinesEx(getCollisionRectangle(), 1.f, RED);
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRectangle() const
{
    Vector2 screenPos = getScreenPos();
    return Rectangle{screenPos.x + (collisionOffset.x * scale), screenPos.y + (collisionOffset.z * scale), (width - (collisionOffset.x + collisionOffset.y)) * scale, (height - (collisionOffset.z + collisionOffset.w)) * scale};
}

void BaseCharacter::update(float dt)
{
    worldPosLastFrame = worldPos;
    // take care of movement
    if (Vector2Length(velocity) > 0)
    {
        texture = run;
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    runningTime += dt;
    if (runningTime > frameTime)
    {
        currentFrame++;
        runningTime = 0;
        if (currentFrame > frameCount)
            currentFrame = 0;
    }
}