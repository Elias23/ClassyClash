#include "raylib.h"
#include "BaseCharacter.h"
#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public BaseCharacter
{
public:
    Character(Vector2 winSize);
    virtual void update(float dt) override;
};

#endif // CHARACTER_H