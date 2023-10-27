#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "game.h"
#include "ui.h"
#include "common.h"

ui_state_t uis;


// Initialize the UI state
void init_ui() {
    uis.selected_option = 0;

    uis.screen_width = DEFAULT_SCREEN_WIDTH;
    uis.screen_height = DEFAULT_SCREEN_HEIGHT;

    // Set the initial screen
    ui_main_menu();
}

// Set the UI state to the main menu
void ui_main_menu() {
    uis.num_items = 3;
    uis.items[0] = "Start Game";
    uis.items[1] = "Options";
    uis.items[2] = "Exit";
    uis.draw = draw_main_menu;
    uis.callback = main_menu_event;
}

// Set the UI state to the combat screen
void ui_combat_menu() {
    uis.num_items = 4;
    uis.items[0] = "Attack";
    uis.items[1] = "Defend";
    uis.items[2] = "Item";
    uis.items[3] = "Run";
    uis.draw = draw_combat_screen;
    uis.callback = combat_menu_event;
}

void ui_attack_menu() {
    uis.num_items = 0;
    for (int i = 0; i < gs.num_players; i++) {
        if (gs.players[i].team != gs.players[gs.current_player].team) {
            uis.items[uis.num_items] = gs.players[i].name;
            uis.num_items++;
        }
    }
    uis.items[uis.num_items++] = "Back";
    uis.draw = draw_combat_screen;
    uis.callback = attack_event;
}

// Callback function for the main menu
void main_menu_event() {
    switch (uis.selected_option) {
    case START_GAME:
        // Start Game
        init_game();
        ui_combat_menu();
        break;
    case OPTIONS:
        // Options
        break;
    case EXIT:
        // Exit
        CloseWindow();
        break;
    }
}

void attack_event() {
    // Get the target -- the selection option is not necessarily the target id
    int target = uis.selected_option;

    if (target == uis.num_items - 1) {
        // Return to previous menu
    }

    // Create an event to attack the selected player.
    event_t *event = calloc(1, sizeof(event_t));
    event->event_type = GAME_EVENT;
    event->event_id = EV_ATTACK_TARGET;
    event->data = target;

    enqueue(event, &event_head, &event_tail);
}

// Callback function for the combat menu
void combat_menu_event() {
    switch (uis.selected_option) {
    case ATTACK: {
        // Attack
        event_t *event = calloc(1, sizeof(event_t));
        event->event_type = GAME_EVENT;
        enqueue(event, &event_head, &event_tail);
        break;
    }
    case DEFEND:
        // Defend
        break;
    case ITEM:
        // Item
        break;
    case RUN:
        // Run
        break;
    }
}

// Draw function for the main menu
int draw_main_menu() {

    // Draw the options
    for (int i = 0; i < uis.num_items; i++) {
        int textX = uis.screen_width / 2 - MeasureText(uis.items[i], 20) / 2;
        int textY = uis.screen_height / 2 - 50 + 40 * i;
        if (i == uis.selected_option) {
            DrawText(TextFormat("> %s <", uis.items[i]), textX, textY, 20,
                     MAROON);
        } else {
            DrawText(TextFormat("  %s  ", uis.items[i]), textX, textY, 20,
                     BLACK);
        }
    }

    return 0;
}

void draw_combatant_view() {
    // Draw the border
    DrawRectangleRoundedLines(
        (Rectangle){20, 20, uis.screen_width - 40, uis.screen_height * 2 / 3 - 20}, 0.1, 10, 2, BLACK);
}

void draw_combat_menu() {
    // Draw the border
    DrawRectangleRoundedLines(
        (Rectangle){20, uis.screen_height * 2 / 3 + 20, uis.screen_width * 1 / 3 - 10, uis.screen_height * 1 / 3 - 40}, 0.1, 10, 2, BLACK);

    // Draw the options
    for (int i = 0; i < uis.num_items; i++) {
        int textX = 40;
        int textY = uis.screen_height * 2 / 3 + 20 * i + 40;
        if (i == uis.selected_option) {
            DrawText(TextFormat("> %s <", uis.items[i]), textX, textY, 20,
                     MAROON);
        } else {
            DrawText(TextFormat("  %s  ", uis.items[i]), textX, textY, 20, BLACK);
        }
    }
}

void draw_combat_log() {
    // Draw the border
    DrawRectangleRoundedLines(
        (Rectangle){uis.screen_width * 1 / 3 + 20, uis.screen_height * 2 / 3 + 20, uis.screen_width * 2 / 3 - 40, uis.screen_height * 1 / 3 - 40},
        0.1, 10, 2, BLACK);

    // Print current player's turn
    DrawText(TextFormat("%s's turn", gs.players[gs.current_player].name),
             uis.screen_width * 1 / 3 + 30, uis.screen_height * 2 / 3 + 30, 20,
             BLACK);
}

void draw_player_health(int player_id) {
    // Get the player's health
    int hp = gs.players[player_id].hp;
    int max_hp = gs.players[player_id].max_hp;

    // Get the player's position
    Vector2 pos = entities[player_id].pos;

    // Get the player's texture
    Texture2D texture = entities[player_id].texture;

    // Get the player's name
    char *name = gs.players[player_id].name;

    float scaled_width = texture.width * 0.2;
    float scaled_height = texture.height * 0.2;

    // Get the player's health bar position
    Vector2 health_pos = { pos.x, pos.y - 20 };

    // Get the player's health bar size
    Vector2 background_size = { scaled_width, 10 };
    Vector2 health_size = { scaled_width * ((float)hp / max_hp), 10 };

    // Draw the player's health bar
    DrawRectangleV(health_pos, background_size, RED);
    DrawRectangleV(health_pos, health_size, GREEN);

    // Draw the player's name
    if (gs.current_player == player_id) {
        DrawText(TextFormat("> %s <", name), pos.x, pos.y + scaled_height + 10, 20, BLACK);
    } else {
        DrawText(TextFormat("  %s  ", name), pos.x, pos.y + scaled_height + 10, 20, BLACK);
    }

    // Draw the player's health
    DrawText(TextFormat("%d/%d", hp, max_hp), pos.x, pos.y - 10, 20, BLACK);
}

void draw_avatar(Image avatar, Vector2 position, int size) {
    Texture2D avatar_texture = LoadTextureFromImage(avatar);
    DrawTextureEx(avatar_texture, position, 0, size / avatar.width, WHITE);
}

// Draw function for the combat screen
int draw_combat_screen() {

    /* Combat Menu */
    draw_combat_menu();

    /* Combat Log */
    draw_combat_log();

    /* Combatant View */
    draw_combatant_view();

    return 0;
}
