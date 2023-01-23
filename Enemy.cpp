#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, float _speed, float dammage)
{
    world_pos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / max_frame;
    height = texture.height;
    speed = _speed;
    dammage_pes_sec = dammage;
    raduis = 25.f;
}

void Enemy::tick(float delta_time)
{
    if (!get_alive())
        return;
    velocity = Vector2Subtract(target->get_screen_pos(), get_screen_pos());
    if (Vector2Length(velocity) < raduis)
        velocity = {};
    Base_character::tick(delta_time);
    if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
    {
        target->take_dammage(dammage_pes_sec * delta_time);
    }
}

void Enemy::Set_target(Character *char_target)
{
    target = char_target;
}

Vector2 Enemy::get_screen_pos()
{
    return Vector2Subtract(world_pos, target->get_world_pos());
}