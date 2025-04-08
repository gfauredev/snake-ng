// État global de l’application, méthode recommandée SDL3
#ifndef __STATE__
#define __STATE__

// #define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>

#include "struct.h"

typedef struct
{
    SDL_Window*   window;   // La fenêtre
    SDL_Renderer* renderer; // Le moteur de rendu, configuré
    snake_t*      snake;    // Pointeur sur la structure du serpent
    fruit_t*      fruit;    // Pointer sur la structure du fruit à manger
    bool          pause;    // Faut-il mettre le jeu en pause ?
} state_t;
#endif
