// Structures communes
#ifndef __STRUCT__
#define __STRUCT__

#include <SDL3/SDL_pixels.h>
#include <stdint.h>

/**
 * @brief structure vecteur
 */
typedef struct vect_s
{
    int8_t x;
    int8_t y;
} vect_t;

/**
 * @brief structure corps du serpent
 */
typedef struct snake_part_s
{
    uint32_t x;
    uint32_t y;
    vect_t   vect;
} snake_part_t;

/**
 * @typedef snake_t
 * @struct snake_s
 * @brief Structure représentant le serpent
 */
typedef struct snake_s
{
    snake_part_t* head; /* < Tête du serpent */
    snake_part_t* body; /* < Corp du serpent (un pointeur de `snake_part_t` ),
                           c'est un tableau de longueur `lenght` */
    uint16_t length; /* < Longueur du corp du serpent (sans la tête `head`) et
                        donc longueur du tableau `snake_body` */
    uint16_t length_body_tab; /* < Longueur max du tableau body */
    uint16_t speed;           /* < vitesse du serpent */

} snake_t;

/**
 * @brief Effet et couleur du fruit
 */
typedef struct
{
    void (*effect)(snake_t* snake);
    SDL_Color color;
} effect_t;

/**
 * @brief Structure fruit
 */
typedef struct fruit_s
{
    SDL_Color color;
    uint32_t  x; //< Position horizontale
    uint32_t  y; //< Position verticale
    void (*effect)(snake_t* snake);
} fruit_t;

#endif
