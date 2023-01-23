#ifndef PROP_H
#define PROP_H

#include "raylib.h"

class Prop
{
private:
    Texture2D texture;
    Vector2 world_pos;
    float scale;

public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knight_pos);
    Rectangle GetCollisionRec(Vector2 knight_pos);
};

#endif