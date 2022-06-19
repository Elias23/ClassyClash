#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main(int argc, char const *argv[])
{
    const int screenWidth = 384;
    const int screenHeight = 384;
    const int targetFPS = 60;
    InitWindow(screenWidth, screenHeight, "ClassyClash");
    SetTargetFPS(targetFPS);
    Vector2 mapPos{0, 0};

    Texture2D map = LoadTexture("sproutLands/WorldMap30x30.png");
    Character knight{Vector2{screenWidth, screenHeight}};

    // animation variables

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        knight.update(deltaTime);
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        Vector2 knightWorldPos = knight.getWorldPos();
        if (knightWorldPos.x < 0 || knightWorldPos.y < 0 || knightWorldPos.x + screenWidth > map.width * 4.f || knightWorldPos.y + screenHeight > map.height * 4.f)
        {
            knight.undoMovement();
        }
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
