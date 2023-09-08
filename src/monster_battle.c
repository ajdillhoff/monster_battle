#include <stdio.h>

#include "raylib.h"

#include "common.h"
#include "ui.h"

int main(void) {
    // Initialization
    init_ui();

    InitWindow(uis.screen_width, uis.screen_height, "Monster Battle");

    // Main game loop
    while (!WindowShouldClose()) {
        run_frame();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
