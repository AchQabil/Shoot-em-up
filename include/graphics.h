#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "MLV/MLV_all.h"

/**
 * Initialise la fenêtre graphique avec la largeur, la hauteur et le titre spécifiés.
 *
 * @param width  Largeur de la fenêtre graphique.
 * @param height Hauteur de la fenêtre graphique.
 * @param title  Titre de la fenêtre graphique.
 */
void graphics_init(int width, int height, const char *title);

/**
 * Efface le contenu de la fenêtre graphique en remplissant avec la couleur noire.
 */
void graphics_clear();

/**
 * Dessine une image à la position spécifiée.
 *
 * @param image L'image à dessiner.
 * @param x     Position horizontale de l'image.
 * @param y     Position verticale de l'image.
 */
void graphics_draw_image(const MLV_Image *image, int x, int y);

/**
 * Met à jour la fenêtre graphique et affiche les dessins à l'écran.
 */
void graphics_update();

/**
 * Nettoie et ferme la fenêtre graphique.
 */
void graphics_cleanup();

#endif