#define SDL_MAIN_USE_CALLBACKS 1
#define WINDOW_WIDTH MAP_WIDTH* PIXEL_PER_SQUARE
#define WINDOW_HEIGHT MAP_HEIGHT* PIXEL_PER_SQUARE

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
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
 * @param txt_scale Multiplicateur de la taille d’affichage
 */
void welcome_message(uint16_t delay_ms, float txt_scale)
{
    SDL_Log("Affichage : Mangez un maximum de fruits!"); // Debug msg
    SDL_Log("");                                         // Saute une ligne
    SDL_Color c = MESSAGE_C;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, txt_scale, txt_scale);
    SDL_RenderDebugText(renderer, 10, (float)WINDOW_HEIGHT / txt_scale / 3,
                        "Mangez un maximum de fruits!");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // Taille normale
    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    SDL_Delay(delay_ms);         // Attend que l’utilisateur ait vu
}

/**
 * @brief Affiche le message de bienvenue pendant delay_ms milisecondes
 * @param delay_ms Durée en milisecondes d’affichage du message, avant début jeu
 * @param txt_scale Multiplicateur de la taille d’affichage
 */
void death_message(uint16_t delay_ms, float txt_scale)
{
    SDL_Log("Affichage : Snake mort, fin du jeu!"); // Debug msg
    SDL_Log("");                                    // Saute une ligne
    SDL_Color c = MESSAGE_C;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, txt_scale, txt_scale);
    SDL_RenderDebugText(renderer, 10, (float)WINDOW_HEIGHT / txt_scale / 3,
                        "Game Over!");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // Taille normale
    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    SDL_Delay(delay_ms);         // Attend que l’utilisateur ait vu
}

/**
 * @brief Initialise le serpent en affichant des messages debug dans la console
 * @param[out] Le serpent initialisé (variable globale)
 */
void log_init_snake()
{
    SDL_Log("Initialisation du serpent");
    snake = init_snake(); // Initialise le serpent du jeu
    SDL_Log("\tLongueur: %d", snake->length);
    SDL_Log("\tVitesse: %d", snake->speed);
    SDL_Log("\tTête (%u, %u) [%d, %d]", snake->head->x, snake->head->y,
            snake->head->vect.x, snake->head->vect.y);
    for (uint16_t i = 0; i < snake->length; i++)
        SDL_Log("\tPartie corps %d (%u, %u) [%d, %d]", i, snake->body[i].x,
                snake->body[i].y, snake->body[i].vect.x, snake->body[i].vect.y);
    SDL_Log(""); // Saute une ligne dans la console
}

/**
 * @brief Déssine (prépare à l’affichage) une partie (tête ou corps) du serpent
 * @param part La partie du serpent à afficher
 */
void draw_snake_part(snake_part_t* part)
{
    SDL_Log("\tDéssin : Case (%u, %u) [%d, %d]", part->x, part->y, part->vect.x,
            part->vect.y);
    SDL_FRect rect; // Définit le rectangle d’une "case"
    rect.w = rect.h = (float)PIXEL_PER_SQUARE;           // Taille de la case
    rect.x          = (float)part->x * PIXEL_PER_SQUARE; // Position horizontale
    rect.y          = (float)part->y * PIXEL_PER_SQUARE; // Position verticale
    SDL_Log("\t\tAffichage : Case (%f, %f)", rect.x, rect.y);
    SDL_RenderFillRect(renderer, &rect); // Prépare la case au rendu
}

/**
 * @brief Déssine (prépare à l’affichage) le serpent, avec les couleurs
 * @param[in] snake Le serpent à afficher (variable globale)
 */
void draw_snake()
{
    SDL_Log("Déssin : Tête du serpent"); // Debug msg
    SDL_Color c = HEAD_C;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    draw_snake_part(snake->head); // Tête
    for (uint16_t i = 0; i < snake->length; i++)
    {
        SDL_Log("Déssin : Corps du serpent, partie %d", i); // Debug msg
        SDL_Color c = BODY_C;
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
        draw_snake_part(&snake->body[i]); // Partie du corps
    }
}

/**
 * @brief Déssine la bordure autour de la zone de jeu
 */
void draw_map_frame()
{
    SDL_Log("Déssin : Bordure"); // Debug msg
    for (uint16_t x = 0; x < MAP_WIDTH; x++)
        for (uint16_t y = 0; y < MAP_HEIGHT; y++)
        {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
            {
                SDL_Color c = BORDER_C;
                SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b,
                                       SDL_ALPHA_OPAQUE);
                SDL_FRect rect; // Définit le rectangle d’une "case"
                rect.w = rect.h = (float)PIXEL_PER_SQUARE; // Taille d’une case
                rect.x = (float)x * PIXEL_PER_SQUARE; // Position horizontale
                rect.y = (float)y * PIXEL_PER_SQUARE; // Position verticale
                SDL_Log("\tAffichage : Bordure (%f, %f)", rect.x, rect.y);
                SDL_RenderFillRect(renderer, &rect); // Prépare rendu case
            }
        }
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
    // Crée la fenêtre
    if (!SDL_CreateWindowAndRenderer("SnakeNG", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    log_init_snake();           // Initialise le serpent (avec debug msgs)
    draw_snake();               // Déssine le serpent entier
    SDL_Log("");                // Saute une ligne dans la console
    welcome_message(2500, 4.0); // Message de bienvenue
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
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS; // Quitte l’application car demandé
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key)
            {
                case SDLK_LEFT:
                    turn_snake(snake, LEFT);
                    break;
                case SDLK_DOWN:
                    turn_snake(snake, DOWN);
                    break;
                case SDLK_UP:
                    turn_snake(snake, UP);
                    break;
                case SDLK_RIGHT:
                    turn_snake(snake, RIGHT);
                    break;
            }
    }
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
    SDL_Log("Programme en cours depuis %" SDL_PRIu64 " secondes",
            SDL_GetTicks() / 1000);
    SDL_Color c = BACKGROUND_C;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);   // RenderDrawColor (noir) sur toute la fenêtre
    draw_map_frame();            // Affiche la bordure du jeu
    move_snake(snake);           // Calcule position du serpent avec vecteurs
    if (check_death(snake))      // Vérifie si le serpent est mort…
        return SDL_APP_SUCCESS;  // et termine le jeu
    draw_snake();                // Déssine le serpent entier
    SDL_RenderPresent(renderer); // Affiche les modifications effectuées
    SDL_Log("");                 // Saute une ligne
    SDL_Delay(DELAY_MS - snake->speed * 50); // DEBUG delay entre frames
    return SDL_APP_CONTINUE;                 // Continue l’exécution normalement
}

/**
 * @brief S’exécute une fois à la toute fin du programme, nettoyage
 * @param appstate L’état du programme SDL3
 * @retval SDL_APP_SUCCESS Stopper normalement l’exécution du programme
 * @retval SDL_APP_FAILURE Stopper le programme, une erreur est survenue
 */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    death_message(2500, 4.0); // Message de fin de jeu
    free_snake_data(snake);   // Libère l’espace mémoire stockant le serpent
}
