#ifndef STAR_H
#define STAR_H

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STARS 300

/**
 * @brief Structure représentant une étoile dans le jeu.
 */
typedef struct {
  int x[MAX_STARS];        // Positions horizontales des étoiles.
  int y[MAX_STARS];        // Positions verticales des étoiles.
  int speed[MAX_STARS];    // Vitesses de déplacement des étoiles.
  int active[MAX_STARS];   // États d'activité des étoiles (actives ou inactives).
  MLV_Image *image[MAX_STARS]; // Images associées aux étoiles.
} Stars;

/**
 * @brief Initialise tous les champs de la structure Stars.
 * @param stars Pointeur vers une structure Stars à initialiser.
 */
void stars_init(Stars *stars);

/**
 * @brief Crée une nouvelle étoile active à une position aléatoire.
 * @param stars Pointeur vers une structure Stars où ajouter la nouvelle étoile.
 * @param num_stars Nombre total d'étoiles à créer.
 */
void stars_create_star(Stars *stars, int num_stars);

/**
 * @brief Met à jour la position des étoiles actives.
 * @param stars Pointeur vers une structure Stars à mettre à jour.
 */
void stars_update(Stars *stars);

/**
 * @brief Dessine toutes les étoiles actives à leur position actuelle.
 * @param stars Pointeur constant vers une structure Stars à dessiner.
 */
void stars_draw(const Stars *stars);

/**
 * @brief Libère la mémoire allouée pour les images des étoiles.
 * @param stars Pointeur vers la structure Stars à nettoyer.
 */
void stars_cleanup(Stars *stars);

#endif
