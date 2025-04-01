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

    for(uint8_t i=0; i<START_BODY_SIZE-1; i++)
    {
        body[i].x = head->x + i*(head->vect.x);
        body[i].y = head->y + i*(head->vect.y);
        body[i].vect = head->vect;
    }

    snake->snake_body = body;
}

void resize_snake_body(snake_t* snake, uint8_t how_much)
{

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