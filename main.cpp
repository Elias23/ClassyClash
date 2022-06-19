#include "raylib.h"
#include "raymath.h"

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

void Character::setScreenPos(Vector2 winSize)
{
    screenPos = Vector2{
        winSize.x / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        winSize.y / 2.0f - 4.0f * (0.5f * (float)texture.height)};
};

void Character::update(float dt)
{
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
    Rectangle source{currentFrame * texture.width / 6.f, 0.0f, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.f, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
};

int main(int argc, char const *argv[])
{
    const int screenWidth = 384;
    const int screenHeight = 384;
    const int targetFPS = 60;
    InitWindow(screenWidth, screenHeight, "ClassyClash");
    SetTargetFPS(targetFPS);
    Vector2 mapPos{0, 0};

    Texture2D map = LoadTexture("sproutLands/WorldMap30x30.png");
    Character knight{};
    knight.setScreenPos(Vector2{screenWidth, screenHeight});

    // animation variables

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        knight.update(deltaTime);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw Map
        DrawTextureEx(map, mapPos, 0, 4, WHITE);
        knight.draw();
        EndDrawing();
    }
    UnloadTexture(map);
    return 0;
}
