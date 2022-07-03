#include "Character.h"
#include "rayMath.h"

Character::Character(Vector2 winSize, Vector2 position, Vector4 collision) : BaseCharacter(collision), windowWidth(winSize.x), windowHeight(winSize.y)
{
    width = texture.width / frameCount;
    height = texture.height;
    worldPos = position;
};

void Character::update(float dt)
{
    if (!getAlive())
        return;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1;
    if (IsKeyDown(KEY_D))
        velocity.x += 1;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1;
    if (IsKeyDown(KEY_S))
        velocity.y += 1;

    BaseCharacter::update(dt);

    if (rightLeft > 0.f)
    {
        weaponOrigin = {0.f, weapon.height * scale};
        weaponOffSet = {35.f, 55.f};
        weaponCollisionRec = {getScreenPos().x + weaponOffSet.x,
                              getScreenPos().y + weaponOffSet.y - weapon.height * scale,
                              weapon.width * scale,
                              weapon.height * scale};
        isAttacking() ? weaponRotation = 35.f : weaponRotation = 0.f;
    }
    else
    {
        weaponOrigin = {weapon.width * scale, weapon.height * scale};
        weaponOffSet = {25.f, 55.f};
        weaponCollisionRec = {getScreenPos().x + weaponOffSet.x - weapon.width * scale,
                              getScreenPos().y + weaponOffSet.y - weapon.height * scale,
                              weapon.width * scale,
                              weapon.height * scale};
        IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? weaponRotation = -35.f : weaponRotation = 0.f;
    }
}

void Character::draw()
{
    if (!getAlive())
        return;
    BaseCharacter::draw();
    // draw sword
    Rectangle source{0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + weaponOffSet.x, getScreenPos().y + weaponOffSet.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, weaponOrigin, weaponRotation, WHITE);
    DrawRectangleLinesEx(weaponCollisionRec, 1.f, BLUE);
}

Vector2 Character::getScreenPos() const
{
    return Vector2{
        windowWidth / 2.0f - scale * (0.5f * static_cast<float>(texture.width) / 6.0f),
        windowHeight / 2.0f - scale * (0.5f * static_cast<float>(texture.height))};
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
        setAlive(false);
}