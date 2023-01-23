#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex)
{
    scale = 4.f;
    world_pos = pos;
    texture = tex;
}

void Prop::Render(Vector2 knight_pos)
{
    Vector2 screen_pos{Vector2Subtract(world_pos, knight_pos)};
    DrawTextureEx(texture, screen_pos, 0.f, scale, WHITE);
    // DrawRectangleLines(
    //     screen_pos.x,
    //     screen_pos.y,
    //     texture.width * scale,
    //     texture.height * scale,
    //     GREEN);
}
Rectangle Prop::GetCollisionRec(Vector2 knight_pos)
{
    Vector2 screen_pos{Vector2Subtract(world_pos, knight_pos)};
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        texture.width * scale,
        texture.height * scale};
}