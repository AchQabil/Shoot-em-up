#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "MLV/MLV_all.h"

/**
 * @brief Initialise la fenêtre graphique avec la largeur, la hauteur et le titre spécifiés.
 * @param width  Largeur de la fenêtre graphique.
 * @param height Hauteur de la fenêtre graphique.
 * @param title  Titre de la fenêtre graphique.
 */
void graphics_init(int width, int height, const char *title);

/**
 * @brief Efface le contenu de la fenêtre graphique en la remplissant avec la couleur noire.
 */
void graphics_clear();

/**
 * @brief Dessine une image à la position spécifiée.
 * @param image L'image à dessiner.
 * @param x     La position horizontale de l'image.
 * @param y     La position verticale de l'image.
 */
void graphics_draw_image(const MLV_Image *image, int x, int y);


/**
 * @brief Dessine un rectangle à la position et avec les dimensions spécifiées, avec la couleur spécifiée.
 * @param x      La position horizontale du rectangle.
 * @param y      La position verticale du rectangle.
 * @param width  La largeur du rectangle.
 * @param height La hauteur du rectangle.
 * @param color  La couleur du rectangle.
 */
void graphics_draw_rectangle(int x, int y, int width, int height, MLV_Color color);

/**
 * @brief Dessine un texte à la position spécifiée, avec la couleur spécifiée.
 * @param text  Le texte à dessiner.
 * @param x     La position horizontale du texte.
 * @param y     La position verticale du texte.
 * @param color La couleur du texte.
 */
void graphics_draw_text(const char* text, int x, int y, MLV_Color color);

/**
 * @brief Met à jour la fenêtre graphique et affiche tous les dessins à l'écran.
 */
void graphics_update();

/**
 * @brief Nettoie les ressources utilisées et ferme la fenêtre graphique.
 */
void graphics_cleanup();

#endif