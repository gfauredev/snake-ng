#ifndef __SNAKE__
#define __SNAKE__

#include <stdbool.h>
#include <stdint.h>

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
 * @param[out] snake pointeur de la structure du serpent
 */
void init_snake_head(snake_t* snake);

/**
 * @private
 * @brief initialise le corps du snake et donc sa longueur (utilise 'param.h')
 * @attention la tête du serpent doit être initialiser d'abord avec la fonction
 * `init_snake_head`
 * @param[out] snake pointeur de la structure du serpent
 */
void init_snake_body(snake_t* snake);

/**
 * @private
 * @brief Aggrandis le tableau contenant le corps du serpent
 * @param[out] snake pointeur de la structure du serpent
 */
void resize_snake_body(snake_t* snake);

/**
 * @brief Le serpent mange un fruit et grandit
 * @param[out] snake Le serpent
 * @param[in] fruit Le fruit mangé
 */
void eat_if_possible(snake_t* snake, fruit_t** fruit);

/**
 * @brief Poursuit le déplacement engagé du serpent, à exécuter à chaque tour
 * @param[out] snake Le serpent à déplacer, qui bouge
 */
void move_snake(snake_t* snake);

/**
 * @brief Change la direction du déplacement du serpent
 * @param[out] snake Le serpent à déplacer, qui bouge
 * @param[in] move Le vecteur de mouvement
 */
void turn_snake(snake_t* snake, vect_t move);

/**
 * @brief Libère l’espace mémoire utilisé par le serpent
 * @param snake Le serpent qui prend un peu trop de place
 */
void free_snake_data(snake_t* snake);

/**
 * @brief Modifie la vitesse par défaut du serpent
 * @param[out] snake Le serpent
 * @param[in] accel Le nombre de cases/pixels par frame à ajouter au mouvement
 */
void accelerate(snake_t* snake, int16_t accel);

/**
 * @brief Vérifie la mort du serpent, à exécuter à chaque tour
 * @param[in] snake Le serpent
 * @return 1 si le serpent est mort, 0 sinon
 */
bool check_death(const snake_t* snake);

#endif
