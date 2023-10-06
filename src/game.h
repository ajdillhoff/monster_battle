#ifndef GAME_H_
#define GAME_H_

#include "raylib.h"
#include "common.h"

#define MAX_ENTITIES 64

typedef struct {
    // visual info
    Vector2 pos;
    Texture2D texture;

    int id;
} entity_t;

typedef struct {
    // stats
    char name[MAX_STR];
    int hp;
    int max_hp;

    // game info
    int id;
    int team;
} playerstate_t;

typedef struct {
    int in_combat;
    int round;

    playerstate_t players[MAX_ENTITIES];
} gamestate_t;

extern gamestate_t gs;
extern entity_t entities[MAX_ENTITIES];

void init_game();

#endif /* GAME_H_ */
