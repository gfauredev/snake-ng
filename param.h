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
#define DELAY_MS 250
#define SPEED_EFFECT_FACTOR 20
#define SPEED_LENGTH_FACTOR 2

// Carte
#define MAP_WIDTH 80
#define MAP_HEIGHT 80
#define PIXEL_PER_SQUARE 10
#define WINDOW_WIDTH (MAP_WIDTH + 1) * PIXEL_PER_SQUARE
#define WINDOW_HEIGHT (MAP_HEIGHT + 1) * PIXEL_PER_SQUARE

// Couleurs (_C)
#define HEAD_C (SDL_Color){63, 255, 63}
#define BODY_C (SDL_Color){63, 127, 63}
#define BORDER_C (SDL_Color){255, 255, 255}
#define FRUIT_NORMAL_C (SDL_Color){255, 0, 0}
#define FRUIT_SPEED_C (SDL_Color){255, 0, 255}
#define FRUIT_DOUBLE_C (SDL_Color){255, 255, 0}
#define MESSAGE_C (SDL_Color){255, 127, 63}
#define BACKGROUND_C (SDL_Color){0, 0, 0}

#endif
