#include "raylib.h"
#ifndef PROP_H
#define PROP_H
class Prop
{
public:
    Prop(Vector2 Pos, Texture2D Tex, Rectangle source, Vector4 collisionOffset);
    void update(float dt);
    void draw(Vector2 CameraPos);
    Rectangle getCollisionRectangle(Vector2 CameraPos);

private:
    Vector2 worldPos{};
    Texture2D texture{};
    Vector2 screenPos{};
    float scale{4.f};
    Rectangle sourceRectangle{};
    Vector4 collisionOffset{};
};
#endif // PROP_H