#include "Character.h"
#include "raymath.h"

Character::Character(int wi_width, int wi_height) : Base_character(),
                                                    win_width(wi_width),
                                                    win_height(wi_height)
{
    width = texture.width / max_frame;
    height = texture.height;
    weapon = LoadTexture("./characters/weapon_sword.png");
    health = 100.f;
    speed = 5.f;
}

void Character::tick(float delta_time)
{
    if (!get_alive())
        return;

    if (IsKeyDown(KEY_LEFT))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_RIGHT))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_UP))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_DOWN))
        velocity.y += 1.0;
    Base_character::tick(delta_time);
    Vector2 origin{};
    Vector2 offset{};
    float rotation = 0;
    if (right_left > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weapon_collision_rec = {
            get_screen_pos().x + offset.x,
            get_screen_pos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = IsKeyDown(KEY_SPACE) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weapon_collision_rec = {
            get_screen_pos().x + offset.x - weapon.width * scale,
            get_screen_pos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotation = IsKeyDown(KEY_SPACE) ? -35.f : 0.f;
    }
    // draw the sword
    Rectangle sourse{
        0.f,
        0.f,
        static_cast<float>(weapon.width) * right_left,
        static_cast<float>(weapon.height)};
    Rectangle dest{
        get_screen_pos().x + offset.x,
        get_screen_pos().y + offset.y,
        weapon.width * (scale),
        weapon.height * (scale)};
    DrawTexturePro(weapon, sourse, dest, origin, rotation, WHITE);

    // DrawRectangleLines(
    //     weapon_collision_rec.x,
    //     weapon_collision_rec.y,
    //     weapon_collision_rec.width,
    //     weapon_collision_rec.height,
    //     GREEN);
}

Vector2 Character::get_screen_pos()
{
    return Vector2{
        static_cast<float>(win_width) / 2.0f - scale * (0.5f * width),
        static_cast<float>(win_height) / 2.0f - scale * (0.5f * height)};
    ;
}

Rectangle Character::get_weapon_collision_rec() const
{
    return weapon_collision_rec;
}

float Character::get_health() const
{
    return health;
}

void Character::take_dammage(float dammage)
{
    health -= dammage;
    if (health <= 0.f)
        set_alive(false);
}
