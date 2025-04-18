#include <SDL3/SDL_log.h>
#include <stdlib.h>

#include "param.h"
#include "snake.h"

void init_snake_head(snake_t* snake)
{
    snake_part_t head_config;
    head_config.x    = SNAKE_START_X;                   // Position horizontale
    head_config.y    = SNAKE_START_Y;                   // Position verticale
    head_config.vect = (vect_t)SNAKE_START_ORIENTATION; // Vecteur de mouvement
    if (DEBUG >= 1)
        SDL_Log("\tTête (%u, %u) [%d, %d]", head_config.x, head_config.y,
                head_config.vect.x, head_config.vect.y);
    snake->head    = malloc(sizeof(snake_part_t));
    *(snake->head) = head_config;
}

void init_snake_body(snake_t* snake)
{
    snake_part_t* body;
    snake_part_t* head = snake->head;
    body               = malloc(BODY_TAB_LENGHT * sizeof(snake_part_t));

    // Initialise les parties du corps du serpent, positionnées avant la tête
    for (uint8_t i = 0; i < START_BODY_SIZE; i++)
    {
        body[i].x    = head->x - (i + 1) * (head->vect.x);
        body[i].y    = head->y - (i + 1) * (head->vect.y);
        body[i].vect = head->vect;
        if (DEBUG >= 1)
            SDL_Log("\tCorps[%d] (%u, %u) <%d, %d>", i, body[i].x, body[i].y,
                    body[i].vect.x, body[i].vect.y);
    }

    snake->length          = START_BODY_SIZE; // Nombre de cases/parties corps
    snake->length_body_tab = BODY_TAB_LENGHT; // Nombre d’octets du corps
    snake->body            = body;
}

void resize_snake_body(snake_t* snake)
{
    snake->body =
        realloc(snake->body,
                sizeof(snake_part_t) * snake->length_body_tab * BODY_RESIZE);
}

void accelerate(snake_t* snake, int16_t accel)
{
    snake->speed = accel;
}

void eat_if_possible(snake_t* snake, fruit_t** fruit)
{
    if (snake->head->x != (*fruit)->x || snake->head->y != (*fruit)->y)
        return; // Le serpent n’est pas sur le fruit
    (*fruit)->effect(snake);
    free(*fruit); // Libère l’espace mémoire
    *fruit = NULL;
}

void move_snake(snake_t* snake)
{
    // Gère le resize du tableau body du serpent si trop long
    if (snake->length == snake->length_body_tab)
        resize_snake_body(snake);

    // Déplace le corps dans le tableau body
    for (uint16_t i = (snake->length - 1); i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    snake->body[0] = *snake->head;         // Tête au début du body
    snake->head->x += snake->head->vect.x; // Déplacement tête selon vecteur
    snake->head->y += snake->head->vect.y; // Déplacement tête selon vecteur
}

void turn_snake(snake_t* snake, vect_t move)
{
    snake->head->vect = move;
}

bool check_death(const snake_t* snake)
{
    // Vérifie pour map
    if ((snake->head->x == MAP_WIDTH) || (snake->head->x == 0))
    {
        if (DEBUG >= 1)
            SDL_Log("Serpent: Mort par sortie verticale (%d, %d)",
                    snake->head->x, snake->head->y);
        return true; // X
    }
    if ((snake->head->y == MAP_HEIGHT) || (snake->head->y == 0))
    {
        if (DEBUG >= 1)
            SDL_Log("Serpent: Mort par sortie horizontale (%d, %d)",
                    snake->head->x, snake->head->y);
        return true; // Y
    }

    // Vérifie pour corps
    for (uint16_t i = 0; i < snake->length; i++)
    {
        if ((snake->head->y == snake->body[i].y) &&
            (snake->head->x == snake->body[i].x))
        {
            if (DEBUG >= 1)
                SDL_Log("Serpent: Mort par autophagie, corps[%d] (%d, %d)", i,
                        snake->body[i].x, snake->body[i].y);
            return true;
        }
    }

    return false;
}

void free_snake_data(snake_t* snake)
{
    free(snake->head);
    free(snake->body);
    free(snake);
}

snake_t* init_snake()
{
    if (DEBUG >= 1)
        SDL_Log("Serpent: Initialisation");
    snake_t* snake = malloc(sizeof(snake_t));
    init_snake_head(snake);
    init_snake_body(snake);
    if (DEBUG >= 2)
        SDL_Log("\tLongueur: %d", snake->length);
    snake->speed = SNAKE_SPEED_START;
    if (DEBUG >= 2)
        SDL_Log("\tVitesse: %d", snake->speed);
    return snake;
}
