#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"
#include "raymath.h"

#ifndef ENEMY_H
#define ENEMY_H
class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, Vector4 collision = Vector4{});
    virtual void update(float dt) override;
    void setTarget(Character *character) { target = character; };
    virtual Vector2 getScreenPos() const override;

private:
    Character *target;
    float damage = 10.f;
    float radius = 22.f;
};
#endif // ENEMY_H