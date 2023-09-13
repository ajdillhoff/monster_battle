#include <stdio.h>

#include "raylib.h"

#include "ui.h"

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
void ui_combat_screen() {
    uis.num_items = 4;
    uis.items[0] = "Attack";
    uis.items[1] = "Defend";
    uis.items[2] = "Item";
    uis.items[3] = "Run";
    uis.draw = draw_combat_screen;
    uis.callback = combat_menu_event;
}

// Callback function for the main menu
void main_menu_event() {
    switch (uis.selected_option) {
    case START_GAME:
        // Start Game
        ui_combat_screen();
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

// Callback function for the combat menu
void combat_menu_event() {
    switch (uis.selected_option) {
    case ATTACK:
        // Attack
        break;
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

    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

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

    EndDrawing();

    return 0;
}

// Draw function for the combat screen
int draw_combat_screen() {

    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    /* Combat Menu */

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

    /* Combat Log */

    // Draw the border
    DrawRectangleRoundedLines(
        (Rectangle){uis.screen_width * 1 / 3 + 20, uis.screen_height * 2 / 3 + 20, uis.screen_width * 2 / 3 - 40, uis.screen_height * 1 / 3 - 40},
        0.1, 10, 2, BLACK);

    // Draw the text
    DrawText("Combat Log", uis.screen_width * 1 / 3 + 30, uis.screen_height * 2 / 3 + 30, 20,
             BLACK);

    EndDrawing();

    return 0;
}
