<<<<<<< HEAD
#ifndef PLAYER_H
#define PLAYER_H

#include "MLV/MLV_all.h"

/* 
 * Structure de données pour représenter le joueur 
 *
 * @param x         Position horizontale du joueur
 * @param y         Position verticale du joueur
 * @param dx        Variation horizontale de la position du joueur à chaque frame
 * @param dy        Variation verticale de la position du joueur à chaque frame
 * @param width     Largeur du joueur
 * @param height    Hauteur du joueur
 * @param life      Points de vie du joueur
 * @param score     Score du joueur
 * @param image     Image représentant le joueur 
 */
typedef struct {
    int x;  
    int y;  
    int dx;     
    int dy;     
    int width;  
    int height; 
    int life;   
    int score;
    MLV_Image *image;
    int move_up;
    int move_down;
    int move_left;
    int move_right;
} Player;

/*
 * Mettre à jour la position du joueur en fonction des variations dx et dy.
 */
void player_update_position(Player* player);


/*
 * Dessiner le joueur à sa position actuelle en utilisant l'image du sprite.
 * @param player        pointeur constant vers une structure Player représentant le joueur
 * @param sprite        pointeur vers une image MLV_Image représentant le sprite du joueur.
 */
void player_draw(const Player* player, const MLV_Image* sprite);


/*
 * Initialise un joueur avec les paramètres spécifiés.
 *
 * @param x         Position horizontale du joueur.
 * @param y         Position verticale du joueur.
 * @param dx        Variation horizontale de la position du joueur à chaque frame.
 * @param dy        Variation verticale de la position du joueur à chaque frame.
 * @param width     Largeur du joueur.
 * @param height    Hauteur du joueur.
 * @param life      Points de vie du joueur.
 * @param score     Score du joueur.
 * @param image     Image représentant le joueur.
 *
 * @return Un pointeur vers le joueur.
 */
Player* player_init(int x, int y, int dx, int dy, int width, int height, int life, int score, MLV_Image* image);

/*
 * Libère la mémoire associée à un joueur.
 *
 * @param player Un pointeur vers le joueur à nettoyer.
 */
void player_cleanup(Player* player);


#endif

=======
// # Fichier d'en-tête pour la gestion du joueur
>>>>>>> 5245a3201a91899b1e5875469e59fd8279c2dfe3
