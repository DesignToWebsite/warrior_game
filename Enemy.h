#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "Base_character.h"
#include "Character.h"

class Enemy : public Base_character
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, float speed, float dammage);
    virtual void tick(float delta_time) override;
    void Set_target(Character *char_target);
    virtual Vector2 get_screen_pos() override;

private:
    Character *target;
    float dammage_pes_sec;
    float raduis;
};

#endif