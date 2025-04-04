#include "snake.h"

void init_snake_head(snake_t* snake)
{
    snake_part_t head_config;
    
    //position
    head_config.x = SNAKE_START_X;
    head_config.y = SNAKE_START_Y;

    //vect
    head_config.vect = (vect_t)SNAKE_START_ORIENTATION;

    snake->head = malloc(sizeof(snake_part_t));
    *(snake->head) = head_config;

}

void init_snake_body(snake_t* snake)
{
    snake_part_t* body;
    snake_part_t* head = snake->head;

    body = malloc(BODY_TAB_LENGHT*sizeof(snake_part_t));

    // Initialise les partie du corp du serpent
    for(uint8_t i=0; i<START_BODY_SIZE; i++)
    {
        body[i].x = head->x + i*(head->vect.x);
        body[i].y = head->y + i*(head->vect.y);
        body[i].vect = head->vect;
    }

    // Gère la longueur du serpent
    snake->lenght           = BODY_TAB_LENGHT;
    snake->lenght_body_tab  = BODY_TAB_LENGHT;

    snake->body = body;
}

void resize_snake_body(snake_t* snake)
{
    realloc(snake->body,sizeof(snake_part_t)*snake->lenght_body_tab*BODY_RESIZE);
}

void accelerate(snake_t* snake, int16_t accel)
{
    snake->speed = accel;
}

void eat(snake_t* snake, fruit_t* fruit)
{
    fruit->effect(snake);
}

void move_snake(snake_t* snake)
{
    // Gère le resize du tableau body du serpent si trop long
    if(snake->lenght == snake->lenght_body_tab)
        resize_snake_body(snake);

    // Deplace le corp dans le tableau body
    for(uint16_t i=(snake->lenght-1); i>0; i--) 
    {
        snake->body[i] = snake->body[i - 1];
    }
    
    // Met la tête dans le body[0]
    snake->body[0] = *snake->head;

    // Dépalce la tête en fonction du vecteur
    snake->head->x += snake->head->vect.x;
    snake->head->y += snake->head->vect.y;

}

void turn_snake(snake_t* snake, vect_t move)
{
    snake->head->vect = move;
}

bool check_death(const snake_t* snake)
{
    // Verifie pour map
    // x
    if((snake->head->x == MAP_WIDTH) || (snake->head->x == 0))
        return true;
    // y
    if((snake->head->y == MAP_HEIGHT) || (snake->head->y == 0))
        return true;

    // Vérifie pour corp
    for(uint16_t i=(snake->lenght-1);i>=0; i--)
    {
        if((snake->head->y == snake->body[i].y) && (snake->head->x == snake->body[i].x))
            return true;
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
    snake_t* snake;
    snake = malloc(sizeof(snake_t));
    init_snake_head(snake);
    init_snake_body(snake);
    snake->speed = SNAKE_SPEED_START;
    return snake;
}