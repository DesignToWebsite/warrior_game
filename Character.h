
#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "Base_character.h"

class Character : public Base_character
{
public:
    Character(int win_w, int win_h);
    virtual void tick(float delta_time) override;
    virtual Vector2 get_screen_pos() override;
    Rectangle get_weapon_collision_rec() const;
    float get_health() const;
    void take_dammage(float dammage);

private:
    int win_width;
    int win_height;
    Texture2D weapon;
    Rectangle weapon_collision_rec;
    float health;
};

#endif