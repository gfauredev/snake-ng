#ifndef __SNAKE__
#define __SNAKE__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "param.h"

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
    vect_t vect;

} snake_part_t;

/**
 * @typedef
 * @brief Structure représentant le serpent
 * @param head Tete du sepent
 * @param snake_body Corp du serpent (un pointeur de `snake_part_t` ), c'est un tableau de longueur `lenght`
 * @param lenght Longueur du corp du serpent (sans la tête `head`) et donc longueur du tableau `snake_body`
 * @param speed vitesse du serpent
 */
typedef struct snake_s
{
    snake_part_t* head;
    snake_part_t* snake_body;
    uint16_t lenght;
    uint16_t speed;

} snake_t;

/**
 * @brief initialise le serpent
 * @return retourne un pointeur vers une structure `snake_t` initialiser avec les différents paramètres dans `param.h`
 */
snake_t* init_snake();

/**
 * @brief initialise la tête du serpent, elle pointe de base vers le haut
 * @param snake pointeur de la structure du serpent
 */
void init_snake_head(snake_t* snake);

/**
 * @brief initialise le corps du snake et donc sa longueur (utilise 'param.h')
 * @attention la tête du serpent doit être initialiser d'abord avec la fonction `init_snake_head`
 * @param snake pointeur de la structure du serpent
 */
void init_snake_body(snake_t* snake);

/**
 * @brief Permet de resize le tableau du corp du serpent
 * @param snake pointeur de la structure du serpent
 * @param how_much de combien le tableau va être multiplié
 */
void resize_snake_body(snake_t* snake, uint8_t how_much);

#endif
