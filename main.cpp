#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

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
    Enemy goblin{Vector2{screenWidth, screenHeight}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};
    goblin.setTarget(&knight);
    Prop props[2]{
        Prop{Vector2{600.0f, 500.0f}, LoadTexture("sproutLands/Objects/Basic Grass Biom things 1.png"), Rectangle{8 * 16, 16, 16, 16}},
        Prop{Vector2{400.0f, 400.0f}, LoadTexture("sproutLands/Objects/Basic Grass Biom things 1.png"), Rectangle{0, 0, 16, 32}}};
    // animation variables

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        knight.update(deltaTime);
        goblin.update(deltaTime);
        Vector2 knightWorldPos = knight.getWorldPos();
        // Check if the knight is going out of the map
        if (knightWorldPos.x < 0 || knightWorldPos.y < 0 || knightWorldPos.x + screenWidth > map.width * 4.f || knightWorldPos.y + screenHeight > map.height * 4.f)
        {
            knight.undoMovement();
        }
        // Check if the knight is colliding with a prop
        for (auto prop : props)
        {
            if (CheckCollisionRecs(knight.getCollisionRectangle(), prop.GetCollisionRectangle(knightWorldPos)))
                knight.undoMovement();
        }

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw Map
        DrawTextureEx(map, mapPos, 0, 4, WHITE);
        for (Prop prop : props)
        {
            prop.draw(knight.getWorldPos());
        }
        knight.draw();
        goblin.draw();
        EndDrawing();
    }
    UnloadTexture(map);
    return 0;
}
