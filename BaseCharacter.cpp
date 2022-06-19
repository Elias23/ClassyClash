#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(/* args */)
{
}

void BaseCharacter::draw()
{
    // Draw the character
    Rectangle source{currentFrame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRectangle()
{
    return Rectangle{screenPos.x, screenPos.y, scale * width, scale * height};
}

void BaseCharacter::update(float dt)
{

    worldPosLastFrame = worldPos;
    runningTime += dt;
    if (runningTime > frameTime)
    {
        currentFrame++;
        runningTime = 0;
        if (currentFrame > frameCount)
            currentFrame = 0;
    }
}