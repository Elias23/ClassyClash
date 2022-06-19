#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex, Rectangle source) : worldPos(pos), texture(tex), sourceRectangle(source)
{
}

void Prop::draw(Vector2 cameraPos)
{
    screenPos = Vector2Subtract(worldPos, cameraPos);
    Rectangle dest{screenPos.x, screenPos.y, sourceRectangle.width * scale, sourceRectangle.height * scale};
    DrawTexturePro(texture, sourceRectangle, dest, Vector2{}, 0.f, WHITE);
};

void Prop::update(float dt){};

Rectangle Prop::GetCollisionRectangle(Vector2 cameraPos)
{
    screenPos = Vector2Subtract(worldPos, cameraPos);
    return Rectangle{screenPos.x, screenPos.y, sourceRectangle.width * scale, sourceRectangle.height * scale};
}
