#include "game.h"
#include "renderer.h"
#include <string.h>
#include <stdio.h>

gamestate_t gs;
entity_t entities[MAX_ENTITIES];

void init_game() {
    gs.in_combat = 1;
    gs.round = 0;

    // Initialize a test player
    gs.players[0].id = 0;
    gs.players[0].team = 0;
    gs.players[0].hp = 10;
    gs.players[0].max_hp = 10;
    strcpy(gs.players[0].name, "Player 1");

    entities[0].id = 0;
    entities[0].pos.x = 0;
    entities[0].pos.y = 0;
    entities[0].texture = LoadTexture("/Users/dillhoff/monster_battle/assets/avatars/1 - k34OMjQ.png");
    printf("[DEBUG] Texture = %d\n", entities[0].texture.id);

    printf("[DEBUG] Loaded the texture and player.\n");

    add_ref(&entities[0]);
}
