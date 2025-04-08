#ifndef __PARAM__
#define __PARAM__

// serpent parametre
// Mouvement
#define UP (vect_t){0, -1}
#define DOWN (vect_t){0, 1}
#define LEFT (vect_t){-1, 0}
#define RIGHT (vect_t){1, 0}

// Tête
#define SNAKE_START_X 50
#define SNAKE_START_Y 50
#define SNAKE_START_ORIENTATION UP

// Corps
#define START_BODY_SIZE 3
#define BODY_TAB_LENGHT 15
#define BODY_RESIZE 2

// Vitesse
#define SNAKE_SPEED_START 1

// Carte
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#define PIXEL_PER_SQUARE 10

#endif
