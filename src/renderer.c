#include "renderer.h"
#include <stdio.h>

ref_entity_t ref_entities[MAX_REFS];
int num_entities = 0;

void add_ref(entity_t *ent) {
    ref_entity_t *ref = &ref_entities[num_entities++];
    ref->texture = ent->texture;
    ref->position = ent->pos;
    ref->rotation = 0;
    ref->tint = WHITE;

    // Set relative size based on UI
    ref->scale = 0.2;
}

void clear_scene() {
    num_entities = 0;
}

void render_frame() {
    for (int i = 0; i < num_entities; i++) {
        ref_entity_t *ref = &ref_entities[i];
        DrawTextureEx(ref->texture, ref->position, ref->rotation, ref->scale, ref->tint);
    }
}
