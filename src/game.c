#include "game.h"
#include "renderer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

gamestate_t gs;
entity_t entities[MAX_ENTITIES];

/*
====================
update_player_positions

Does not dynamically update to UI layout changes.
Assumes 4 players maximum per team.
====================
*/
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
            entities[i].pos.y = num_left * (combat_view.height / 3) + 50;

            num_left++;
        } else {
            // Set the player's position to the right side of the screen
            entities[i].pos.x = combat_view.width * 0.8;
            entities[i].pos.y = num_right * (combat_view.height / 3) + 50;

            num_right++;
        }
    }
}

void init_game() {
    gs.in_combat = 1;
    gs.round = 1;
    gs.num_players = 0;

    // Initialize a test player
    gs.players[0].id = 0;
    gs.players[0].team = 0;
    gs.players[0].hp = 100;
    gs.players[0].max_hp = 100;
    gs.players[0].accuracy = 0;
    gs.players[0].defense = 10;
    gs.players[0].damage = 20;
    gs.players[0].has_turn = 1;
    strcpy(gs.players[0].name, "Player 1");

    entities[0].id = 0;
    entities[0].texture = LoadTexture("assets/1 - PtKcq3j.png");

    gs.num_players++;

    gs.current_player = 0;

    gs.players[1].id = 1;
    gs.players[1].team = 1;
    gs.players[1].hp = 100;
    gs.players[1].max_hp = 100;
    gs.players[1].accuracy = 20;
    gs.players[1].defense = 10;
    gs.players[1].damage = 10;
    gs.players[1].has_turn = 1;
    strcpy(gs.players[1].name, "Player 2");

    entities[1].id = 1;
    entities[1].texture = LoadTexture("assets/2 - msN2dA9.png");

    gs.num_players++;

    gs.players[2].id = 2;
    gs.players[2].team = 1;
    gs.players[2].hp = 120;
    gs.players[2].max_hp = 120;
    gs.players[2].accuracy = 20;
    gs.players[2].defense = 10;
    gs.players[2].damage = 10;
    gs.players[2].has_turn = 1;
    strcpy(gs.players[2].name, "Player 3");

    entities[2].id = 2;
    entities[2].texture = LoadTexture("assets/4 - JDrqfVv.png");

    gs.num_players++;
}

int calculate_hit(int accuracy, int defense) {
    int hit = 70;

    // Calculate hit
    hit += (accuracy - defense);

    // Flip a coin with %hit probability
    hit = rand() % 100 < hit;

    return hit;
}

/*
====================
game_attack_target

Executes the attack action on the selected target.
====================
*/
void game_attack_target(int target) {

    // Find the selected target
    for (int i = 0; i < gs.num_players; i++) {
        if (gs.players[i].team != gs.players[gs.current_player].team) {
            if (target == 0) {
                target = i;
                break;
            } else {
                target--;
            }
        }
    }

    // Update rules of game
    if (calculate_hit(gs.players[gs.current_player].accuracy, gs.players[target].defense)) {
        printf("%s hit %s\n", gs.players[gs.current_player].name, gs.players[target].name);
        printf("Is defending = %d\n", gs.players[target].is_defending);
        float defense_negation = gs.players[target].is_defending * 0.5 * gs.players[target].defense;
        printf("Defense negation = %f\n", defense_negation);
        int damage = gs.players[gs.current_player].damage - defense_negation;
        int does_crit = rand() % 100 < 10;
        gs.players[target].hp -= damage + does_crit * damage;
        printf("%s hit %s for %d damage.\n", gs.players[gs.current_player].name, gs.players[target].name, damage + does_crit * damage);
    } else {
        printf("%s missed %s\n", gs.players[gs.current_player].name, gs.players[target].name);
    }

    gs.players[gs.current_player].has_turn = 0;

    return;
}

/*
====================
game_player_use_item

Uses an item.
====================
*/
void game_player_defend() {
    gs.players[gs.current_player].is_defending = 1;
    gs.players[gs.current_player].has_turn = 0;

    printf("[DEBUG] Player defending!\n");
}

/*
====================
game_player_use_item

Uses an item.
====================
*/
void game_player_use_item(int item_id) {
    gs.players[gs.current_player].hp += 20;

    gs.players[gs.current_player].has_turn = 0;
}

/*
====================
update_game_state

Updates the game state.
====================
*/
void update_game_state() {
    // Check if the next player should go
    if (gs.players[gs.current_player].has_turn == 0) {
        gs.current_player = (gs.current_player + 1) % gs.num_players;
        ui_combat_menu();
    }

    // Update round
    int i = 0;

    for (i = 0; i < gs.num_players; i++) {
        if (gs.players[i].has_turn && gs.players[i].hp > 0) {
            break;
        }
    }

    if (i == gs.num_players) {
        // Check if the game is over
        int num_left = 0;
        int num_right = 0;
        
        for (int i = 0; i < gs.num_players; i++) {
            if (gs.players[i].hp > 0) {
                if (gs.players[i].team == 0) {
                    num_left++;
                } else {
                    num_right++;
                }
            }
        }

        if (num_left == 0 || num_right == 0) {
            gs.in_combat = 0;
            ui_main_menu();
            return;
        }

        gs.round++;
        printf("Round %d\n", gs.round);
        for (int i = 0; i < gs.num_players; i++) {
            gs.players[i].has_turn = 1;
        }
    }
}

/*
====================
handle_game_event

Handles game events.
====================
*/
void handle_game_event(event_t *event) {
    switch (event->event_id) {
        case EV_ATTACK_ACTION:
            // Show target selection
            ui_attack_menu();
            break;
        case EV_ATTACK_TARGET:
            game_attack_target(event->data);
            break;
        case EV_PLAYER_DEFEND:
            game_player_defend();
            break;
        case EV_PLAYER_ITEM_ACTION:
            ui_item_menu();
            break;
        case EV_PLAYER_USE_ITEM:
            game_player_use_item(event->data);
            break;
    }

    update_game_state();
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
        draw_player_health(i);
    }

    // Render the combat screen
    render_frame();
}
