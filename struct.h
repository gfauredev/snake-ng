// Structures communes
#ifndef __STRUCT__
#define __STRUCT__

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
 * @typedef
 * @brief Structure représentant le serpent
 * @param head Tete du sepent
 * @param snake_body Corp du serpent (un pointeur de `snake_part_t` ), c'est un
 * tableau de longueur `lenght`
 * @param lenght Longueur du corp du serpent (sans la tête `head`) et donc
 * longueur du tableau `snake_body`
 * @param speed vitesse du serpent
 */
typedef struct snake_s
{
    snake_part_t* head;
    snake_part_t* snake_body;
    uint16_t      lenght;
    uint16_t      speed;

} snake_t;

/**
 * @brief Structure fruit
 */
typedef struct fruit_s
{
    uint8_t  color;
    uint32_t x; //< Position horizontale
    uint32_t y; //< Position verticale
    void (*effect)(snake_t *snake);
} fruit_t;
#endif
