#ifndef COMMON_H_
#define COMMON_H_

typedef struct {
    int in_combat;
} gamestate_t;

void init_game();
int event_loop();
int run_frame();

#endif /* COMMON_H_ */
