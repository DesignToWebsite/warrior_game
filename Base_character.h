
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class Base_character
{
public:
    Base_character();
    // Character(int win_w, int win_h);
    Vector2 get_world_pos();
    Vector2 get_world_pos_last_frame();
    virtual void tick(float delta_time);
    void undo_movement();
    void unload_texture();
    Rectangle GetCollisionRec();
    virtual Vector2 get_screen_pos() = 0;
    bool get_alive();
    void set_alive(bool bol);

protected:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    // Vector2 screen_pos;
    Vector2 world_pos;
    Vector2 world_pos_last_frame;
    Vector2 velocity;
    float speed;
    // 1=> facing right, -1 : facing left
    float right_left;
    // animation variables
    float running_time;
    int frame;
    int max_frame;
    float update_time;
    float width;
    float height;
    float scale;

private:
    bool alive;
};

#endif