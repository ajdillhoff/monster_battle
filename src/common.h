#ifndef COMMON_H_
#define COMMON_H_

#include "queue_utils.h"

#define MAX_STR 128
#define MAX_EVENTS 128

typedef enum {
    GAME_EVENT,
    UI_EVENT,
    INPUT_EVENT
} event_type_t;

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
