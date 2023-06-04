#ifndef PLAYER_H
#define PLAYER_H

#include "MLV/MLV_all.h"

/**
 * @brief Structure de données pour représenter le joueur.
 * @param x         Position horizontale du joueur.
 * @param y         Position verticale du joueur.
 * @param dx        Variation horizontale de la position du joueur à chaque frame.
 * @param dy        Variation verticale de la position du joueur à chaque frame.
 * @param width     Largeur du joueur.
 * @param height    Hauteur du joueur.
 * @param image     Image représentant le joueur.
 * @param move_up   Indicateur du mouvement vers le haut du joueur.
 * @param move_down Indicateur du mouvement vers le bas du joueur.
 * @param move_left Indicateur du mouvement vers la gauche du joueur.
 * @param move_right Indicateur du mouvement vers la droite du joueur.
 */
typedef struct {
    int x;  
    int y;  
    int dx;     
    int dy;     
    int width;  
    int height; 
    MLV_Image *image;
    int move_up;
    int move_down;
    int move_left;
    int move_right;
} Player;

/**
 * @brief Met à jour la position du joueur en fonction des variations dx et dy.
 * @param player Pointeur vers une structure Player représentant le joueur.
 */
void player_update_position(Player* player);


/**
 * @brief Dessine le joueur à sa position actuelle en utilisant l'image du sprite.
 * @param player Pointeur constant vers une structure Player représentant le joueur.
 * @param sprite Pointeur constant vers une image MLV_Image représentant le sprite du joueur.
 */
void player_draw(const Player* player, const MLV_Image* sprite);


/**
 * @brief Initialise un joueur avec les paramètres spécifiés.
 * @param x         Position horizontale du joueur.
 * @param y         Position verticale du joueur.
 * @param dx        Variation horizontale de la position du joueur à chaque frame.
 * @param dy        Variation verticale de la position du joueur à chaque frame.
 * @param width     Largeur du joueur.
 * @param height    Hauteur du joueur.
 * @param image     Image représentant le joueur.
 *
 * @return Un pointeur vers le joueur nouvellement initialisé.
 */
Player* player_init(int x, int y, int dx, int dy, int width, int height, int life, int score, MLV_Image* image);

/**
 * @brief Libère la mémoire associée à un joueur.
 * @param player Un pointeur vers le joueur à nettoyer.
 */
void player_cleanup(Player* player);


#endif