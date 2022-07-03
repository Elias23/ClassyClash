#include "raylib.h"
#include "raymath.h"
#include "main.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include <iostream>

int DEBUG_MODE = 0;

#define ENEMY_COUNT 4
#define PROP_COUNT 4
#define MAP_COUNT 4

// Draw
void draw(const float deltaTime,
          const int screenWidth,
          const int screenHeight,
          Character &knight,
          Enemy (&goblins)[ENEMY_COUNT],
          Prop (&props)[PROP_COUNT],
          Texture2D (&map)[MAP_COUNT],
          Vector2 &mapPos,
          float &runningTime,
          int &currentFrame)
{

    const int frameCount = 4;
    const float frameTime = 1.0f / 6.f;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Draw Map
    runningTime += deltaTime;
    if (runningTime > frameTime)
    {
        currentFrame++;
        runningTime = 0;
        if (currentFrame >= frameCount)
            currentFrame = 0;
    }
    DrawTextureEx(map[currentFrame], mapPos, 0, 4, WHITE);
    for (Prop prop : props)
    {
        prop.draw(knight.getWorldPos());
    }
    if (!knight.getAlive())
    {
        DrawText("You died!", screenWidth / 2 - MeasureText("You died!", 20) / 2, screenHeight / 2, 20, RED);
        EndDrawing();
        return;
    }
    else
    {
        std::string text = "HP: ";
        text.append(std::to_string(knight.getHealth()));
        DrawText(text.c_str(), 10, 10, 20, BLACK);
    }
    knight.draw();
    for (auto &goblin : goblins)
    {
        goblin.draw();
    }

    EndDrawing();
}
// Update
void update(const float deltaTime,
            const int screenWidth,
            const int screenHeight,
            Character &knight,
            Enemy (&goblins)[ENEMY_COUNT],
            Prop (&props)[PROP_COUNT],
            Texture2D (&map)[MAP_COUNT],
            Vector2 &mapPos)
{
    knight.update(deltaTime);
    for (auto &&goblin : goblins)
    {
        goblin.update(deltaTime);
    }
    Vector2 knightWorldPos = knight.getWorldPos();
    // Check if the knight is going out of the map
    if (knightWorldPos.x < 0 || knightWorldPos.y < 0 || knightWorldPos.x + screenWidth > map[0].width * 4.f || knightWorldPos.y + screenHeight > map[0].height * 4.f)
    {
        knight.undoMovement();
    }
    // Check if the knight is colliding with a prop
    for (auto prop : props)
    {
        if (CheckCollisionRecs(knight.getCollisionRectangle(), prop.getCollisionRectangle(knightWorldPos)))
            knight.undoMovement();
    }

    if (knight.isAttacking())
    {
        for (auto &&goblin : goblins)
        {
            if (CheckCollisionRecs(knight.getWeaponCollisionRec(), goblin.getCollisionRectangle()))
            {
                goblin.setAlive(false);
            }
        }
    }
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
}

int main(int argc, char const *argv[])
{
    const int screenWidth = 384;
    const int screenHeight = 384;
    const int targetFPS = 60;
    float runningTime = 0;
    int currentFrame = 0;
    InitWindow(screenWidth, screenHeight, "ClassyClash");
    SetTargetFPS(targetFPS);
    Vector2 mapPos{0, 0};
    Texture2D map[MAP_COUNT]{LoadTexture("sproutLands/WorldMap30x30_1.png"),
                             LoadTexture("sproutLands/WorldMap30x30_2.png"),
                             LoadTexture("sproutLands/WorldMap30x30_3.png"),
                             LoadTexture("sproutLands/WorldMap30x30_4.png")};
    Character knight{Vector2{screenWidth, screenHeight}, Vector2{555, 555}, Vector4{3, 3, 1, 1}};
    Enemy goblins[ENEMY_COUNT]{
        {Vector2{545, 2345}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"), Vector4{1, 1, 1, 2}},
        {Vector2{456, 126}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"), Vector4{1, 1, 1, 2}},
        {Vector2{454, 234}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png"), Vector4{1, 1, 1, 2}},
        {Vector2{234, 987}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png"), Vector4{1, 1, 1, 2}}};
    for (auto &&goblin : goblins)
    {
        goblin.setTarget(&knight);
    }

    Prop props[PROP_COUNT]{
        Prop{Vector2{600.0f, 500.0f}, LoadTexture("sproutLands/Objects/Basic_Grass_Biom_things_1.png"), Rectangle{8 * 16, 16, 16, 16}, Vector4{1, 1, 2, 3}}, // Stone
        Prop{Vector2{400.0f, 400.0f}, LoadTexture("sproutLands/Objects/Basic_Grass_Biom_things_1.png"), Rectangle{0, 0, 16, 32}, Vector4{1, 1, 0, 4}},       // Tall Tree
        Prop{Vector2{700.0f, 450.0f}, LoadTexture("sproutLands/Objects/Basic_Grass_Biom_things_1.png"), Rectangle{16, 0, 32, 32}, Vector4{1, 1, 0, 4}},      // Fat Tree
        Prop{Vector2{350.0f, 700.0f}, LoadTexture("sproutLands/Objects/Basic_Grass_Biom_things_1.png"), Rectangle{48, 0, 32, 32}, Vector4{1, 1, 0, 4}}       // Fat Tree with Apples
    };
    // animation variables

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        update(deltaTime, screenWidth, screenHeight, knight, goblins, props, map, mapPos);

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        draw(deltaTime, screenWidth, screenHeight, knight, goblins, props, map, mapPos, runningTime, currentFrame);
    }
    for (auto mapTexture : map)
        UnloadTexture(mapTexture);
    return 0;
}
