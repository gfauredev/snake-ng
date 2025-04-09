// Rendu et état du jeu
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

#include "param.h"
#include "strings.h"
#include "struct.h"

/* Affiche un message en grand pendant delay_ms milisecondes
 */
void render_message(char msg[], state_t* state, float txt_scale,
                    uint16_t delay_ms)
{
    if (DEBUG >= 1)
        SDL_Log(RENDER_MSG_MSG, msg, delay_ms); // Debug msg
    SDL_Color c = MESSAGE_C;
    SDL_SetRenderDrawColor(state->renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(state->renderer, txt_scale, txt_scale);
    SDL_RenderDebugText(state->renderer, MSG_MARGIN,
                        (float)WINDOW_HEIGHT / txt_scale / 3, msg);
    char score[MAX_SCORE_CHARS];
    SDL_snprintf(score, MAX_SCORE_CHARS, SCORE_MSG,
                 state->snake->length - START_BODY_SIZE);
    if (state->snake->length > START_BODY_SIZE)
        SDL_RenderDebugText(state->renderer, MSG_MARGIN,
                            (float)WINDOW_HEIGHT / txt_scale / 3 + MSG_MARGIN,
                            score);
    SDL_SetRenderScale(state->renderer, 1.0f, 1.0f); // Normal
    SDL_RenderPresent(state->renderer); // Affiche les modifications
    SDL_Delay(delay_ms);                // Attend que l’utilisateur ait vu
}

/**
 * @private
 * @brief Déssine (prépare à l’affichage) une case du jeu
 * @param x Position horizontale de la case
 * @param y Position verticale de la case
 * @param render Le moteur de rendu
 */
void render_square(float x, float y, SDL_Renderer* render)
{
    if (DEBUG >= 3)
        SDL_Log(RENDER_SQUARE_MSG, x, y);
    SDL_FRect rect; // Définit le rectangle d’une "case"
    rect.w = rect.h = (float)PIXEL_PER_SQUARE;     // Taille de la case
    rect.x          = (float)x * PIXEL_PER_SQUARE; // Position horizontale
    rect.y          = (float)y * PIXEL_PER_SQUARE; // Position verticale
    SDL_RenderFillRect(render, &rect);             // Affiche la case
}

/* Déssine (prépare à l’affichage) le serpent, avec les couleurs
 */
void render_snake(state_t* state)
{
    if (DEBUG >= 1)
        SDL_Log(RENDER_SNAKE_MSG, state->snake->head->x,
                state->snake->head->y); // DEBUG
    SDL_Color head_c = HEAD_C;          // Définit la couleur de la tête
    SDL_Color body_c = BODY_C;          // Définit la couleur du corps
    SDL_SetRenderDrawColor(state->renderer, head_c.r, head_c.g, head_c.b,
                           SDL_ALPHA_OPAQUE);
    render_square(state->snake->head->x, state->snake->head->y,
                  state->renderer); // Tête
    SDL_SetRenderDrawColor(state->renderer, body_c.r, body_c.g, body_c.b,
                           SDL_ALPHA_OPAQUE);
    for (uint16_t i = 0; i < state->snake->length; i++)
    {
        if (DEBUG >= 2)
            SDL_Log(RENDER_SNAKE_BODY_MSG, i, state->snake->body[i].x,
                    state->snake->body[i].y); // DEBUG
        render_square(state->snake->body[i].x, state->snake->body[i].y,
                      state->renderer); // Partie du corps
    }
}

/* Déssine la bordure autour de la zone de jeu
 */
void render_map_borders(SDL_Renderer* render)
{
    if (DEBUG >= 1)
        SDL_Log(RENDER_BORDERS_MSG, MAP_WIDTH,
                MAP_HEIGHT); // DEBUG
    SDL_Color c = BORDER_C;
    SDL_SetRenderDrawColor(render, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    for (uint16_t x = 0; x <= MAP_WIDTH; x++)
        for (uint16_t y = 0; y <= MAP_HEIGHT; y++)
            if (x == 0 || x == MAP_WIDTH || y == 0 || y == MAP_HEIGHT)
                render_square(x, y, render);
}

/* Déssine (prépare à l’affichage) un fruit
 */
void render_fruit(state_t* state)
{
    if (DEBUG >= 1)
        SDL_Log(RENDER_FRUIT_MSG, state->fruit->x, state->fruit->y,
                state->fruit->effect);
    SDL_SetRenderDrawColor(state->renderer, state->fruit->color.r,
                           state->fruit->color.g, state->fruit->color.b,
                           SDL_ALPHA_OPAQUE);
    render_square(state->fruit->x, state->fruit->y, state->renderer);
}
