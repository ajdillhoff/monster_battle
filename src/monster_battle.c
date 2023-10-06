#include <stdio.h>

#include "raylib.h"

#include "common.h"

int main(void) {
    // Initialization
    init();

    // Main game loop
    while (!WindowShouldClose()) {
        run_frame();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
