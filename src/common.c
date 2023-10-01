#include <raylib.h>

#include "common.h"
#include "ui.h"

gamestate_t gs;

// Initialize the game
void init_game() {
    gs.in_combat = 0;

    init_ui();

    InitWindow(uis.screen_width, uis.screen_height, "Monster Battle");
}

// Poll for input and other events
int event_loop() {

    if (IsKeyPressed(KEY_UP)) {
        uis.selected_option--;
        if (uis.selected_option < 0) {
            uis.selected_option = uis.num_items - 1;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        uis.selected_option++;
        if (uis.selected_option >= uis.num_items) {
            uis.selected_option = 0;
        }
    } else if (IsKeyPressed(KEY_ENTER)) {
        uis.callback();
    }

    return 0;
}

// Process events and update the screen
int run_frame() {
    // Listen to input or other events
    event_loop();

    // Render the current screen
    uis.draw();
    
    if (gs.in_combat) {
        // Update game events

        // Render the combat screen

    }

    return 0;
}