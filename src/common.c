#include <raylib.h>

#include "common.h"
#include "ui.h"
#include "game.h"
#include "renderer.h"


// Initialize the game
void init() {
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

    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    if (gs.in_combat) {
        draw_active_frame();
    }

    // Render the UI elements (regardless of combat)
    uis.draw();

    EndDrawing();

    return 0;
}
