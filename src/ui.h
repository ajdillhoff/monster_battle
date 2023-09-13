#ifndef UI_H_
#define UI_H_

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define MAX_MENUITEMS 10

// Event definitions
#define START_GAME 0
#define OPTIONS 1
#define EXIT 2
#define ATTACK 0
#define DEFEND 1
#define ITEM 2
#define RUN 3

typedef struct {
    int selected_option;

    int num_items;
    const char *items[MAX_MENUITEMS];

    int (*draw)();
    void (*callback)();

    int screen_width;
    int screen_height;
} ui_state_t;

void init_ui();
void ui_main_menu();
void ui_combat_screen();
void main_menu_event();
void combat_menu_event();
int draw_main_menu();
int draw_combat_screen();

extern ui_state_t uis;

#endif /* UI_H_ */
