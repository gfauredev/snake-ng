#ifndef __SNAKE__
#define __SNAKE__

#include <stdbool.h>
#include <stdint.h>
// #include <stdio.h>
// #include <stdlib.h>

#include "param.h"
#include "struct.h"

/**
 * @brief initialise le serpent
 * @return retourne un pointeur vers une structure `snake_t` initialiser avec
 * les différents paramètres dans `param.h`
 */
snake_t* init_snake();

/**
 * @private
 * @brief initialise la tête du serpent, elle pointe de base vers le haut
 * @param snake pointeur de la structure du serpent
 */
void init_snake_head(snake_t* snake);

/**
 * @private
 * @brief initialise le corps du snake et donc sa longueur (utilise 'param.h')
 * @attention la tête du serpent doit être initialiser d'abord avec la fonction
 * `init_snake_head`
 * @param snake pointeur de la structure du serpent
 */
void init_snake_body(snake_t* snake);

/**
 * @private
 * @brief Permet de resize le tableau du corp du serpent
 * @param snake pointeur de la structure du serpent
 * @param how_much de combien le tableau va être multiplié
 */
void resize_snake_body(snake_t* snake, uint8_t how_much);

/**
 * @brief Le serpent mange un fruit et grandit
 * @param snake Le serpent
 * @param fruit Le fruit mangé
 */
void eat(snake_t* snake, fruit_t fruit);
/**
 * @brief Poursuit le déplacement engagé du serpent, à exécuter à chaque tour
 * @param snake Le serpent à déplacer, qui bouge
 */
void move_snake(snake_t* snake);

/**
 * @brief Change la direction du déplacement du serpent
 * @param snake Le serpent à déplacer, qui bouge
 * @param move Le vecteur de mouvement
 */
void turn_snake(snake_t* snake, vect_t move);

/**
 * @brief Libère l’espace mémoire utilisé par le serpent
 * @param snake Le serpent qui prend un peu trop de place
 */
void free_snake_data(snake_t* snake);

/**
 * @brief Modifie la vitesse par défaut du serpent
 * @param snake Le serpent
 * @param accel Le nombre de cases/pixels par frame à ajouter au mouvement
 */
void accelerate(snake_t* snake, int16_t accel);

/**
 * @brief Vérifie la mort du serpent, à exécuter à chaque tour
 * @param snake Le serpent
 * @return 1 si le serpent est mort, 0 sinon
 */
bool check_death(snake_t* snake);
#endif
