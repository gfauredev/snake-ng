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
 * @brief Affiche le message de bienvenue pendant delay_ms milisecondes
 * @param delay_ms Durée en milisecondes d’affichage du message, avant début jeu
 */
void welcome_message(uint16_t delay_ms)
{
    SDL_Log("Bienvenue sur le jeu Snake New Generation !");
    SDL_Log("Affichage : Mangez un maximum de fruits!"); // Debug msg
    SDL_SetRenderDrawColor(renderer, 255, 127, 63, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, 4.0f, 4.0f); // Texte quadruple
    SDL_RenderDebugText(renderer, 10, (float)WINDOW_HEIGHT / 4 / 2,
                        "Mangez un maximum de fruits!");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // Texte normal
    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    SDL_Delay(delay_ms);         // Attend que l’utilisateur ait vu
}

/**
 * @brief Déssine (prépare à l’affichage) une partie (tête ou corps) du serpent
 * @param part La partie du serpent à afficher
 */
void draw_snake_part(snake_part_t* part)
{
    SDL_FRect rect;                     // Définit le rectangle d’une "case"
    rect.w = rect.h = PIXEL_PER_SQUARE; // Taille de la case
    rect.x          = part->x * PIXEL_PER_SQUARE; // Position horizontale
    rect.y          = part->y * PIXEL_PER_SQUARE; // Position verticale
    SDL_Log("Déssin : Partie du serpent en (%f, %f)", rect.x, rect.y);
    SDL_RenderFillRect(renderer, &rect); // Prépare la case au rendu
}

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
    snake = init_snake();    // Initialise le serpent du jeu
    welcome_message(2500);   // Message de bienvenue
    SDL_Log("");             // Saute une ligne dans la console
    return SDL_APP_CONTINUE; // Nous sommes arrivés ici: continuer normalement
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
    // Définit la couleur noire, en remplit la fenêtre, puis passe au blanc
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); // RenderDrawColor sur toute la fenêtre
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Déssine le serpent
    draw_snake_part(snake->head); // Tête
    for (uint16_t i = 0; i < snake->lenght; i++)
        draw_snake_part(snake->body); // Partie du corps

    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    SDL_Log("");                 // Saute une ligne
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
