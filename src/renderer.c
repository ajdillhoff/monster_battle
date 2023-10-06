#include "renderer.h"
#include <stdio.h>

ref_entity_t ref_entities[MAX_REFS];
int num_entities = 0;

void add_ref(entity_t *ent) {
    ref_entity_t *ref = &ref_entities[num_entities++];
    ref->texture = ent->texture;
    ref->position = ent->pos;
    ref->size = (Vector2){ent->texture.width, ent->texture.height};
    ref->rotation = 0;
    ref->tint = WHITE;
}

void render_frame() {
    for (int i = 0; i < num_entities; i++) {
        ref_entity_t *ref = &ref_entities[i];
        DrawTextureV(ref->texture, ref->position, ref->tint);
    }
}
