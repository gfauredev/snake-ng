#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <stdint.h>
#include <stdlib.h>

#include "fruit.h"
#include "param.h"
#include "render.h"
#include "snake.h"
#include "state.h"
#include "struct.h"

/**
 * @brief Fonction lancée une fois au tout début du programme, pour initialiser
 * @param state État de l’application, spécifique à SDL3
 * @param argc Nombre de paramètres passés en ligne de commande
 * @param argv Valeurs des paramètres passés en ligne de commande
 * @retval SDL_APP_CONTINUE Continuer l’exécution du programme, tout va bien
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
SDL_AppResult SDL_AppInit(void** state_ptr, int argc, char* argv[])
{
    SDL_Log("Bienvenue sur le jeu Snake New Generation !"); // CLI msg
    SDL_Log("");                                            // Saute une ligne
    // Définit les métadonnées de l’application (fenêtre)
    SDL_SetAppMetadata("SnakeNG", "1.0", "snake-ng");
    // Initialise SDL3
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // Initialise l’état global de l’application
    state_t* state = (state_t*)SDL_malloc(sizeof(state_t));
    // Crée la fenêtre
    if (!SDL_CreateWindowAndRenderer("SnakeNG", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &state->window, &state->renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    state->snake = init_snake(); // Initialise le serpent (avec messages DEBUG)
    render_snake(state);         // Déssine le serpent entier
    render_message("Mangez un maximum de fruits!", state, 3, 1000);
    state->fruit = NULL;     // Initialise le fruit à NULL
    state->pause = 0;        // Ne met pas le jeu en pause
    *state_ptr   = state;    // Passe l’état de l’application
    return SDL_APP_CONTINUE; // Nous sommes arrivés ici: continuer normalement
}

/**
 * @brief "Interruption" est exécutée lorsqu’un évennement survient (clavier…)
 * @param state L’état du programme SDL3
 * @param event L’évennement survenu en question (voir SDL_events.h)
 * @retval SDL_APP_CONTINUE Continuer l’exécution du programme, tout va bien
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
SDL_AppResult SDL_AppEvent(void* state_ptr, SDL_Event* event)
{
    state_t* state = (state_t*)state_ptr; // Récupère l’état du jeu
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS; // Quitte l’application car demandé
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key)
            {
                case SDLK_LEFT:
                    if (state->snake->head->vect.x != 1)
                        turn_snake(state->snake, LEFT);
                    break;
                case SDLK_DOWN:
                    if (state->snake->head->vect.y != -1)
                        turn_snake(state->snake, DOWN);
                    break;
                case SDLK_UP:
                    if (state->snake->head->vect.y != 1)
                        turn_snake(state->snake, UP);
                    break;
                case SDLK_RIGHT:
                    if (state->snake->head->vect.x != -1)
                        turn_snake(state->snake, RIGHT);
                    break;
                case SDLK_SPACE:
                    if (state->pause)
                    {
                        if (DEBUG >= 1)
                            SDL_Log("Jeu: Reprise du jeu");
                        state->pause = 0; // Reprendre
                    }
                    else
                    {
                        if (DEBUG >= 1)
                            SDL_Log("Jeu: Jeu en pause");
                        render_message("Jeu en pause...", state, 3, 50);
                        state->pause = 1; // Mettre en pause
                    }
                    break;
                case SDLK_ESCAPE:
                    return SDL_APP_SUCCESS; // Quitte l’application car demandé
                    break;
            }
    }
    return SDL_APP_CONTINUE;
}

/**
 * @brief État principal du jeu, exécutée de nombreuses fois par seconde
 * @param state L’état du programme SDL3
 * @retval SDL_APP_CONTINUE Continuer l’exécution du programme, tout va bien
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
SDL_AppResult SDL_AppIterate(void* state_ptr)
{
    state_t* state = (state_t*)state_ptr; // Récupère l’état global du jeu
    if (state->pause)
        return SDL_APP_CONTINUE; // Sortir immédiatement si pause
    if (DEBUG >= 1)
        SDL_Log("Jeu: En cours depuis %" SDL_PRIu64 " secondes",
                SDL_GetTicks() / 1000);
    SDL_Color c = BACKGROUND_C;
    SDL_SetRenderDrawColor(state->renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(state->renderer);    // Couleur de fond sur toute la fenêtre
    render_map_borders(state->renderer); // Affiche la bordure du jeu
    if (!state->fruit)                   // S’il n’y a pas de fruit…
        state->fruit = spawn_fruit();    // en fais apparaître un
    else
    {
        render_fruit(state); // Affiche le fruit s’il existe
        eat_if_possible(state->snake, &state->fruit);
    }
    move_snake(state->snake);      // Calcule position du serpent avec vecteurs
    if (check_death(state->snake)) // Vérifie si le serpent est mort…
        return SDL_APP_SUCCESS;    // et termine le jeu
    render_snake(state);           // Déssine le serpent entier
    SDL_RenderPresent(state->renderer); // Affiche les modifications effectuées
    uint16_t delay_ms = DELAY_MS - state->snake->speed * SPEED_EFFECT_FACTOR -
                                    state->snake->length * SPEED_LENGTH_FACTOR >
                                0
                            ? DELAY_MS -
                                  state->snake->speed * SPEED_EFFECT_FACTOR -
                                  state->snake->length * SPEED_LENGTH_FACTOR
                            : 1;
    SDL_Delay(delay_ms);
    if (DEBUG >= 1)
        SDL_Log("Jeu: %f mouvements (images) par secondes",
                (float)1000 / delay_ms); // Vitesse actuelle
    SDL_Log("");                         // Saute une ligne
    return SDL_APP_CONTINUE;             // Continue l’exécution normalement
}

/**
 * @brief S’exécute une fois à la toute fin du programme, nettoyage
 * @param state L’état du programme SDL3
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
void SDL_AppQuit(void* state_ptr, SDL_AppResult result)
{
    state_t* state = (state_t*)state_ptr; // Récupère l’état global du jeu
    // Message de fin de jeu
    render_message("Game Over!", state, 4, 2000);

    // Libère l’espace mémoire stockant le serpent
    free_snake_data(state->snake);
    // Libère l’espace mémoire stockant le fruit
    free(state->fruit);
    // Libère l’espace mémoire stockant l’état global du jeu
    free(state);
}
