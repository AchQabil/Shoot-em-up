#ifndef GAME_H
#define GAME_H

#include "MLV/MLV_all.h"
#include "player.h"
#include "stars.h"
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 700        /* Largeur de l'écran de jeu */
#define HEIGHT 800       /* Hauteur de l'écran de jeu */
#define PLAYER_WIDTH 120  /* Largeur du joueur */
#define PLAYER_HEIGHT 120 /* Hauteur du joueur */
#define ENEMY_WIDTH 40   /* Largeur de l'ennemi */
#define ENEMY_HEIGHT 40  /* Hauteur de l'ennemi */
#define BULLET_WIDTH 5   /* Largeur du projectile */
#define BULLET_HEIGHT 20 /* Hauteur du projectile */
#define STAR_WIDTH 25   /* Hauteur de stars */
#define STAR_HEIGHT 25    /* Largeur de stars */
#define MAX_BULLETS 10   /* Nombre maximum de projectiles */
#define MAX_ENEMIES 10   /* Nombre maximum d'ennemis */
#define ENEMY_COUNT 10   /* Nombre des ennemies dans le jeu */

/*
 * Structure de données pour représenter le jeu
 *
 */
typedef struct {
  Player player;
  Stars stars;
  MLV_Image *player_sprite;
} Game;


/*
 * Initialise le jeu
 */
void init_game(Game *game);


/*
 * Dessine le jeu
 */
void draw_game(const Game *game);


/*
 * Met à jour le jeu
 */
void update_game(Game *game);


/*
 * Gère les entrées de jeu
 */
void handle_input_game(Game *game, bool *quit);


/*
 * Nettoie le jeu
 */
void clean_game(Game *game);

#endif
