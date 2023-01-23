#include "Base_character.h"
#include "raymath.h"

Base_character::Base_character() : max_frame(6), update_time(1.f / 12.f)
{
    texture = LoadTexture("./characters/knight_idle_spritesheet.png");
    idle = LoadTexture("./characters/knight_idle_spritesheet.png");
    run = LoadTexture("./characters/knight_run_spritesheet.png");
    speed = 4.0;
    right_left = 1.f;
    running_time = 0;
    frame = 0;
    max_frame = 6;
    update_time = 1.f / 12.f;
    width = 0;
    height = 0;
    scale = 4.0;
    world_pos = {0.f, 0.f};
    alive = true;
}

Vector2 Base_character::get_world_pos()
{
    return world_pos;
}

Vector2 Base_character::get_world_pos_last_frame()
{
    return world_pos_last_frame;
}

void Base_character::undo_movement()
{
    world_pos = world_pos_last_frame;
}

Rectangle Base_character::GetCollisionRec()
{
    return Rectangle{
        get_screen_pos().x,
        get_screen_pos().y,
        width * scale,
        height * scale};
}

void Base_character::tick(float delta_time)
{
    if (!get_alive())
        return;
    world_pos_last_frame = world_pos;
    // animation
    running_time += delta_time;
    if (running_time >= update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame >= max_frame)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0)
    {
        // set world_pos = world_pos - velocity
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), speed));

        right_left = velocity.x < 0.f ? -1.f : 1.f;
        // set the character
        texture = run;
    }
    else
    {
        // set the character
        texture = idle;
    }
    velocity = {};
    // draw the character
    Rectangle source{
        frame * width,
        0.f,
        right_left * width,
        height,
    };
    Rectangle dest{
        get_screen_pos().x,
        get_screen_pos().y,
        scale * width,
        scale * height};
    Vector2 origin{};

    DrawTexturePro(texture, source, dest, origin, 0, WHITE);
}

void Base_character::unload_texture()
{
    UnloadTexture(texture);
    UnloadTexture(run);
    UnloadTexture(idle);
}

bool Base_character::get_alive()
{
    return alive;
}
void Base_character::set_alive(bool bol)
{
    alive = bol;
}