#ifndef __PARAM__
#define __PARAM__

// Carte
#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define PIXEL_PER_SQUARE 25
#define WINDOW_WIDTH (MAP_WIDTH + 1) * PIXEL_PER_SQUARE
#define WINDOW_HEIGHT (MAP_HEIGHT + 1) * PIXEL_PER_SQUARE

// Mouvement
#define UP (vect_t){0, -1}
#define DOWN (vect_t){0, 1}
#define LEFT (vect_t){-1, 0}
#define RIGHT (vect_t){1, 0}
// Tête du serpent
#define SNAKE_START_X (uint16_t)MAP_WIDTH / 2
#define SNAKE_START_Y (uint16_t)MAP_HEIGHT / 2
#define SNAKE_START_ORIENTATION UP
// Corps du serpent
#define START_BODY_SIZE 3
#define BODY_TAB_LENGHT 15
#define BODY_RESIZE 2
// Vitesse du serpent
#define SNAKE_SPEED_START 1
#define DELAY_MS 250
#define SPEED_EFFECT_FACTOR 20
#define SPEED_LENGTH_FACTOR 2

// Couleurs (_C)
#define BACKGROUND_C (SDL_Color){0, 0, 0}
#define BORDER_C (SDL_Color){180, 195, 180}
#define HEAD_C (SDL_Color){63, 255, 63}
#define BODY_C (SDL_Color){63, 127, 63}
#define FRUIT_NORMAL_C (SDL_Color){255, 0, 0}
#define FRUIT_SPEED_C (SDL_Color){255, 0, 255}
#define FRUIT_DOUBLE_C (SDL_Color){255, 255, 0}
#define MESSAGE_C (SDL_Color){255, 127, 63}

// Messages
#define MSG_MARGIN 10
#define MAX_SCORE_CHARS sizeof(MSG_MARGIN) + 5
// Profondeur des messages de debug, 0 pour désactiver
#define DEBUG 2
#endif
