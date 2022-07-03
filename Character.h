#include "raylib.h"
#include "BaseCharacter.h"
#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public BaseCharacter
{
public:
    Character(Vector2 winSize, Vector2 position, Vector4 collisionOffset = Vector4{});
    virtual void update(float dt) override;
    virtual void draw() override;
    virtual Vector2 getScreenPos() const override;
    Rectangle getWeaponCollisionRec() const { return weaponCollisionRec; };
    bool isAttacking() const { return IsMouseButtonDown(MOUSE_BUTTON_LEFT); };
    float getHealth() const { return health; };
    void takeDamage(float damage);

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon = LoadTexture("characters/weapon_sword.png");
    Rectangle weaponCollisionRec{};
    Vector2 weaponOrigin{};
    Vector2 weaponOffSet{};
    float weaponRotation{};
    float health{100.f};
};

#endif // CHARACTER_H