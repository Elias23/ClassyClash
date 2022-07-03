#include "Prop.h"
#include "raymath.h"
#include "main.h"

Prop::Prop(Vector2 pos, Texture2D tex, Rectangle source, Vector4 collisionOffset) : worldPos(pos), texture(tex), sourceRectangle(source), collisionOffset(collisionOffset)
{
}

void Prop::draw(Vector2 cameraPos)
{
    screenPos = Vector2Subtract(worldPos, cameraPos);
    Rectangle dest{screenPos.x, screenPos.y, sourceRectangle.width * scale, sourceRectangle.height * scale};
    if (DEBUG_MODE)
        DrawRectangleLinesEx(getCollisionRectangle(cameraPos), 1.f, RED);
    DrawTexturePro(texture, sourceRectangle, dest, Vector2{}, 0.f, WHITE);
};

void Prop::update(float dt){};

Rectangle Prop::getCollisionRectangle(Vector2 cameraPos)
{
    screenPos = Vector2Subtract(worldPos, cameraPos);
    return Rectangle{screenPos.x + (collisionOffset.x * scale), screenPos.y + (collisionOffset.z * scale), (sourceRectangle.width - (collisionOffset.x + collisionOffset.y)) * scale, (sourceRectangle.height - (collisionOffset.z + collisionOffset.w)) * scale};
}
