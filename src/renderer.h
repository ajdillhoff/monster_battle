#ifndef RENDERER_H_
#define RENDERER_H_

#include "raylib.h"

#define MAX_REFS 128

typedef struct {
    Texture2D texture;
    Vector2 position;
    Vector2 size;
    float rotation;
    Color tint;
} ref_entity_t;

void add_ref(ref_entity_t *ref);
void render_frame();

#endif // RENDERER_H_