// Rendu et état du jeu
#ifndef __RENDER__
#define __RENDER__

#include "state.h"

/**
 * @brief Affiche msg pendant delay_ms milisecondes
 * @param msg Le message à afficher
 * @param state L’état global du jeu
 * @param txt_scale Multiplicateur de la taille d’affichage
 * @param delay_ms Durée en milisecondes d’affichage du message, avant début jeu
 */
void render_message(char msg[], state_t* state, float txt_scale,
                    uint16_t delay_ms);
/**
 * @brief Déssine (prépare à l’affichage) le serpent, avec les couleurs
 * @param state L’état global du jeu
 */
void render_snake(state_t* state);

/**
 * @brief Déssine La bordure autour de la zone de jeu
 * @param render Le moteur de rendu
 */
void render_map_borders(SDL_Renderer* render);

/**
 * @brief Déssine (prépare à l’affichage) le fruit
 * @param state L’état global du jeu
 */
void render_fruit(state_t* state);
#endif
