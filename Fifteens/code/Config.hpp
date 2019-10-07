#pragma once
#include "CreateSprite.hpp"

#define TILES_COUNT 4
#define TILE_SIZE 60 

#define SCREEN_HEIGHT 539
#define SCREEN_WIDTH 960

#define BACKGROUND_SPEED -15

#define X_TABLE 240
#define Y_TABLE 55

#define Y_PLANET_ORDER  Y_TABLE + TILE_SIZE / 2

#define X_FIELD	30 + X_TABLE
#define Y_FIELD 100 + Y_TABLE

#define EMPTINESS -1
#define BLACK_HOLE 0
#define MARS 1
#define MOON 2
#define EARTH 3

#define X_SHUFFLE X_FIELD + 7 + map.SIZE * TILE_SIZE
#define Y_SHUFFLE Y_FIELD
#define SHUFFLE_WIDTH 142
#define SHUFFLE_HEIGHT 49