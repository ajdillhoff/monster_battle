#ifndef COMMON_H_
#define COMMON_H_

#include "queue_utils.h"

#define MAX_STR 128
#define MAX_EVENTS 128

// Event definitions
typedef enum {
    GAME_EVENT,
    UI_EVENT
} event_type_t;

typedef enum {
    EV_ATTACK_ACTION,
    EV_ATTACK_TARGET,
    EV_PLAYER_DEFEND,
    EV_PLAYER_ITEM_ACTION,
    EV_PLAYER_USE_ITEM
} entity_event_t;

typedef struct {
    int event_type;
    int event_id;
    int data;
} event_t;

void init();
int event_loop();
int run_frame();

extern Node *event_head;
extern Node *event_tail;

#endif /* COMMON_H_ */
