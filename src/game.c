#include "game.h"
#include "renderer.h"
#include <string.h>
#include <stdio.h>

gamestate_t gs;
entity_t entities[MAX_ENTITIES];

void update_player_positions() {
    Rectangle combat_view = { 0, 0, uis.screen_width, uis.screen_height * (2.0 / 3.0) };

    int num_left = 0;
    int num_right = 0;

    // Loop through all players
    for (int i = 0; i < gs.num_players; i++) {
        // If the player is on the left team
        if (gs.players[i].team == 0) {
            // Set the player's position to the left side of the screen
            entities[i].pos.x = combat_view.width * 0.05;
            entities[i].pos.y = num_left * (combat_view.height / 4) + 25;

            num_left++;
        } else {
            // Set the player's position to the right side of the screen
            entities[i].pos.x = combat_view.width * 0.8;
            entities[i].pos.y = num_right * (combat_view.height / 4) + 25;

            num_right++;
        }
    }
}

void init_game() {
    gs.in_combat = 1;
    gs.round = 0;
    gs.num_players = 0;

    // Initialize a test player
    gs.players[0].id = 0;
    gs.players[0].team = 0;
    gs.players[0].hp = 10;
    gs.players[0].max_hp = 10;
    strcpy(gs.players[0].name, "Player 1");

    entities[0].id = 0;
    entities[0].texture = LoadTexture("assets/1 - PtKcq3j.png");
    printf("[DEBUG] Texture = %d\n", entities[0].texture.id);

    gs.num_players++;

    printf("[DEBUG] Loaded the texture and player.\n");

    gs.players[1].id = 1;
    gs.players[1].team = 0;
    gs.players[1].hp = 10;
    gs.players[1].max_hp = 10;
    strcpy(gs.players[1].name, "Player 2");

    entities[1].id = 1;
    entities[1].texture = LoadTexture("assets/2 - msN2dA9.png");

    gs.num_players++;
}

/*
====================
draw_active_frame

Configures player entities and draws the active frame.
====================
*/
void draw_active_frame() {
    // Clear the scene
    clear_scene();

    // Update game events

    // Update player positions
    update_player_positions();

    // Add the player entities to the renderer
    for (int i = 0; i < gs.num_players; i++) {
        add_ref(&entities[i]);
    }

    // Render the combat screen
    render_frame();
}
