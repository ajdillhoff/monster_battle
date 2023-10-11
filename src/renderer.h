#ifndef RENDERER_H_
#define RENDERER_H_

#include "raylib.h"
#include "game.h"
#include "ui.h"

extern ui_state_t uis;

#define MAX_REFS 128

typedef struct {
    Texture2D texture;
    Vector2 position;
    float rotation;
    float scale;
    Color tint;
} ref_entity_t;

void add_ref(entity_t *ent);
void render_frame();

#endif // RENDERER_H_
