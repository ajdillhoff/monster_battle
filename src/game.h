#ifndef GAME_H_
#define GAME_H_

#include "raylib.h"

#define MAX_ENTITIES 64

typedef struct {
    int hp;

    Vector2 pos;

    Texture2D texture;
} entity_t;

#endif /* GAME_H_ */