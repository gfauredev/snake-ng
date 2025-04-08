// Rendu et état du jeu
#ifndef __RENDER__
#define __RENDER__

#include "state.h"

/**
 * @brief Affiche un message en grand pendant delay_ms milisecondes
 * @param msg Le message à afficher
 * @param render Le moteur de rendu
 * @param txt_scale Multiplicateur de la taille d’affichage
 * @param delay_ms Durée en milisecondes d’affichage du message, avant début jeu
 */
void render_message(char msg[], SDL_Renderer* render, float txt_scale,
                    uint16_t delay_ms);
/**
 * @brief Déssine (prépare à l’affichage) le serpent, avec les couleurs
 * @param[in] snake Le serpent à afficher (variable globale)
 */
void render_snake(state_t* state);

/**
 * @brief Déssine la bordure autour de la zone de jeu
 */
void render_map_borders(SDL_Renderer* render);

/**
 * @brief Déssine (prépare à l’affichage) un fruit
 * @param part Le fruit à afficher
 */
void render_fruit(state_t* state);
#endif
