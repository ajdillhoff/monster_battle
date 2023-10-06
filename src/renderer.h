#ifndef RENDERER_H_
#define RENDERER_H_

#include "raylib.h"
#include "game.h"

#define MAX_REFS 128

typedef struct {
    Texture2D texture;
    Vector2 position;
    Vector2 size;
    float rotation;
    Color tint;
} ref_entity_t;

void add_ref(entity_t *ent);
void render_frame();

#endif // RENDERER_H_
