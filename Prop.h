#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 Pos, Texture2D Tex, Rectangle source);
    void update(float dt);
    void draw(Vector2 CameraPos);
    Rectangle GetCollisionRectangle(Vector2 CameraPos);

private:
    Vector2 worldPos{};
    Texture2D texture{};
    Vector2 screenPos{};
    float scale{4.f};
    Rectangle sourceRectangle{};
};