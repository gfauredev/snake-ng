#define SDL_MAIN_USE_CALLBACKS 1
#define WINDOW_WIDTH MAP_WIDTH* PIXEL_PER_SQUARE
#define WINDOW_HEIGHT MAP_HEIGHT* PIXEL_PER_SQUARE

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <stdint.h>
#include <stdlib.h>

#include "param.h"
#include "snake.h"
#include "struct.h"

static SDL_Window*   window   = NULL; // La fenêtre
static SDL_Renderer* renderer = NULL; // Le moteur de rendu, configuré
snake_t*             snake;           // Le serpent du jeu

/**
 * @brief Fonction lancée une fois au tout début du programme, pour initialiser
 * @param appstate État de l’application, spécifique à SDL3
 * @param argc Nombre de paramètres passés en ligne de commande
 * @param argv Valeurs des paramètres passés en ligne de commande
 * @retval SDL_APP_CONTINUE Continuer l’exécution du programme, tout va bien
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    // Définit les métadonnées de l’application (fenêtre)
    SDL_SetAppMetadata("SnakeNG", "1.0", "snake-ng");
    // Initialise SDL3
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // Crée la fenêtre
    if (!SDL_CreateWindowAndRenderer("SnakeNG", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // Initialisations d’objets du jeu
    snake = init_snake(); // Le serpent
    // Message de bienvenue fenêtre et terminal, couleur définie à blanc
    SDL_Log("Affichage : Mangez un maximum de fruits !");
    SDL_SetRenderDrawColor(renderer, 255, 127, 63, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, 4.0f, 4.0f); // Quadruple texte
    SDL_RenderDebugText(renderer, 10, (float)WINDOW_HEIGHT / 4 / 2,
                        "Mangez un maximum de fruits!");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // Taille normale
    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    SDL_Delay(2500); // Attend quelques secondes que l’utilisateur ait vu

    // Si nous sommes arrivés jusque là, continuer normalement
    return SDL_APP_CONTINUE;
}

/**
 * @brief "Interruption" est exécutée lorsqu’un évennement survient (clavier…)
 * @param appstate L’état du programme SDL3
 * @param event L’évennement survenu en question (voir SDL_events.h)
 * @retval SDL_APP_CONTINUE Continuer l’exécution du programme, tout va bien
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS; // Quitte l’application car demandé
    return SDL_APP_CONTINUE;
}

/**
 * @brief État principal du jeu, exécutée de nombreuses fois par seconde
 * @param appstate L’état du programme SDL3
 * @retval SDL_APP_CONTINUE Continuer l’exécution du programme, tout va bien
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    // Définit la couleur noire et remplis la feneêtre de celle-ci
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); // RenderDrawColor sur toute la fenêtre

    // Définit notre rectangle d’une "case", définit la couleur blanche
    SDL_FRect rect;
    rect.w = rect.h = PIXEL_PER_SQUARE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Déssine la tête du serpent
    rect.x = snake->head->x;
    rect.y = snake->head->y;
    SDL_RenderFillRect(renderer, &rect);
    // Déssine le corps du serpent
    for (uint16_t i = 0; i < snake->lenght; i++)
    {
        rect.x = snake->body[i].x;
        rect.y = snake->body[i].y;
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    return SDL_APP_CONTINUE;     // Continue l’exécution normalement
}

/**
 * @brief S’exécute une fois à la toute fin du programme, nettoyage
 * @param appstate L’état du programme SDL3
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    // free(snake); // Libère l’espace mémoire stockant le serpent
}
