#include "raylib.h"
#include "raymath.h"
#include "Base_character.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    int window_width = 384;
    int window_height = 384;
    InitWindow(window_width, window_height, "map");

    Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos = {0, 0};
    const float map_scale{4.0};

    Character knight(window_width, window_height);

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin(Vector2{800.f, 300.f},
                 LoadTexture("./characters/goblin_idle_spritesheet.png"),
                 LoadTexture("./characters/goblin_run_spritesheet.png"),
                 2.f,
                 10.f);

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("./characters/slime_idle_spritesheet.png"),
        LoadTexture("./characters/slime_run_spritesheet.png"),
        2.1f,
        5.f};

    Enemy goblin2(Vector2{1500.f, 700.f},
                  LoadTexture("./characters/goblin_idle_spritesheet.png"),
                  LoadTexture("./characters/goblin_run_spritesheet.png"),
                  3.f,
                  10.f);

    Enemy slime2{
        Vector2{2000.f, 900.f},
        LoadTexture("./characters/slime_idle_spritesheet.png"),
        LoadTexture("./characters/slime_run_spritesheet.png"),
        3.f,
        5.f};

    Enemy *enemies[]{
        &goblin,
        &slime,
        &goblin2,
        &slime2};

    for (auto enemy : enemies)
    {
        enemy->Set_target(&knight);
    }
    bool enemy_alive = true;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // // draw the map
        map_pos = Vector2Scale(knight.get_world_pos(), -1.f);
        DrawTextureEx(map, map_pos, 0, map_scale, WHITE);

        for (auto enemy : enemies) // enemies are alive
        {
            if (enemy->get_alive())
            {
                enemy_alive = true;
                break;
            }
            else
                enemy_alive = false;
        }

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.get_world_pos());
        }
        if (!knight.get_alive()) // character is not alive
        {
            DrawText("Game Over!", window_width / 4, window_height / 2 - 50, 40, RED);
            EndDrawing();
            continue;
        }
        else if (!enemy_alive) // if all the enemies died
        {
            DrawText("You win!", window_width / 2 - 60, window_height / 2 - 50, 40, BLACK);
            EndDrawing();
            continue;
        }
        else // character is  alive
        {
            DrawText(TextFormat("dammage : %.2f", knight.get_health()), 120.f, 10, 30, BLACK);
        }

        knight.tick(GetFrameTime());
        for (auto eneny : enemies)
        {
            eneny->tick(GetFrameTime());
        }
        // goblin.tick(GetFrameTime());
        // check map
        if (knight.get_world_pos().x < 0.f ||
            knight.get_world_pos().y < 0.f ||
            knight.get_world_pos().x + window_width > map.width * map_scale ||
            knight.get_world_pos().y + window_width > map.height * map_scale)
        {
            knight.undo_movement();
        }
        // check collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(knight.GetCollisionRec(), prop.GetCollisionRec(knight.get_world_pos())))
            {
                knight.undo_movement();
            }
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.get_weapon_collision_rec()))
                    enemy->set_alive(false);
            }
        }

        EndDrawing();
    }
    UnloadTexture(map);

    knight.unload_texture();
    CloseWindow();
    return 0;
}
