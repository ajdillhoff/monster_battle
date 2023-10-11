#include "game.h"
#include "renderer.h"
#include <string.h>
#include <stdio.h>

gamestate_t gs;
entity_t entities[MAX_ENTITIES];

Vector2 get_position(int team) {
    if (team) {
        return (Vector2){ 0.1 * uis.screen_width, 0.1 * uis.screen_height };
    } else {
        return (Vector2){ 0.8 * uis.screen_width, 0 * uis.screen_height };
    }
}

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
    entities[0].pos = get_position(gs.players[0].team);
    entities[0].texture = LoadTexture("/Users/dillhoff/monster_battle/assets/avatars/1 - k34OMjQ.png");
    printf("[DEBUG] Texture = %d\n", entities[0].texture.id);

    printf("[DEBUG] Loaded the texture and player.\n");

    gs.players[1].id = 1;
    gs.players[1].team = 1;
    gs.players[1].hp = 10;
    gs.players[1].max_hp = 10;
    strcpy(gs.players[1].name, "Player 2");

    entities[1].id = 1;
    entities[1].pos = get_position(gs.players[1].team);
    entities[1].texture = LoadTexture("/Users/dillhoff/monster_battle/assets/avatars/2 - msN2da9.png");

    add_ref(&entities[0]);
    add_ref(&entities[1]);
}
