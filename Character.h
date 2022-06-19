#include "raylib.h"

class Character
{
public:
    Vector2 getWorldPos() const { return worldPos; }
    void setScreenPos(Vector2 screenPos);
    void update(float dt);
    void draw();

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};

    // 1 : facing right, -1 : facing left
    float rightLeft = 1;
    // animation
    float runningTime = 0;
    int currentFrame = 0;
    const int frameCount = 6;
    const float frameTime = 1.0f / 12.f;
    const float speed = 4.f;
};