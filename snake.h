#ifndef SNAKE
#define SNAKE

#include <stdint.h>

/**
 * @brief structure vecteur
 */
typedef struct vect_s
{
    uint32_t x;
    uint32_t y;
} vect_t;

/**
 * @brief structure corps du serpent
 */
typedef struct snake_s
{
    uint32_t x;
    uint32_t y;
    vect_t vect_t;

} snake_t;

/**
 * @brief tableau représentant le serpent
 */
snake_t snake_body[];

/**
 * @brief initialise le corps du snake
 * @param snake_body pointeur du premier 
 */
void init_snake_body(snake_t* snake_body);


#endif
