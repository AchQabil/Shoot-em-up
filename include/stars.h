#ifndef STAR_H
#define STAR_H

#include "MLV/MLV_all.h"

#define MAX_STARS 300

/* Structure pour représenter les étoiles
 *
 * @param x[MAX_STARS]      Positions horizontales des étoiles
 * @param y[MAX_STARS]      Positions verticales des étoiles
 * @param speed[MAX_STARS]  Vitesses de déplacement des étoiles
 * @param active[MAX_STARS] État d'activité des étoiles (actives ou inactives)
 * @param image[MAX_STARS]  Images associées aux étoiles
 */
typedef struct {
  int x[MAX_STARS];
  int y[MAX_STARS];
  int speed[MAX_STARS];
  int active[MAX_STARS];
  MLV_Image *image[MAX_STARS];
} Stars;

/* 
 * Initialise tous les éléments de Stars
 *
 */
void stars_init(Stars *stars);

/* 
 * Crée une nouvelle étoile active à une position aléatoire.
 *
 */
void stars_create_star(Stars *stars, int num_stars);

/* 
 * Met à jour la position des étoiles actives.
 * Si une étoile atteint le bas de l'écran, elle devient inactive.
 *
 */
void stars_update(Stars *stars);

/* 
 * Dessine toutes les étoiles actives à leur position actuelle.
 *
 */
void stars_draw(const Stars *stars);

/* 
 * Libère la mémoire allouée pour les images des étoiles.
 *
 * @param stars   Pointeur vers la structure Stars à nettoyer.
 */
void stars_cleanup(Stars *stars);

#endif
