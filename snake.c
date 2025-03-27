#include "snake.h"

void init_snake_head(snake_t* snake)
{
    snake_patrt_t head_config;
    
    //position
    head_config.x = SNAKE_START_X;
    head_config.y = SNAKE_START_Y;

    //vect
    head_config.vect_t = (vect_t)SNAKE_START_ORIENTATION;

    snake->head = malloc(sizeof(snake_patrt_t));
    *(snake->head) = head_config;

}

void init_snake_body(snake_t* snake)
{
    
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