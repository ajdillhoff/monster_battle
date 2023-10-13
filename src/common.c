#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "ui.h"
#include "game.h"
#include "renderer.h"
#include "queue_utils.h"

Node *event_head = NULL;
Node *event_tail = NULL;

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

    // Get next event from the queue
    event_t *event = dequeue(&event_head, &event_tail);

    if (event != NULL) {
        printf("Event type: %d\n", event->event_type);

        switch (event->event_type) {
        case GAME_EVENT:
            // Game event
            handle_game_event(event);
            break;
        default:
            printf("TODO: Handle event type %d\n", event->event_type);
        }

        free(event);
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
