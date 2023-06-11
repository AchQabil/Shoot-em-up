#include "../include/game.h"
#include "../include/player.h"

void player_update_position(Player *player)
{
  // Mettre à jour la position du joueur en fonction des états de mouvement
  if (player->move_up)
  {
    player->y -= player->dy;
  }
  if (player->move_down)
  {
    player->y += player->dy;
  }
  if (player->move_left)
  {
    player->x -= player->dx;
  }
  if (player->move_right)
  {
    player->x += player->dx;
  }

  // Limiter la position du joueur à l'écran de jeu
  if (player->x < 0)
  {
    player->x = 0;
  }
  else if (player->x + player->width > WIDTH)
  {
    player->x = WIDTH - player->width;
  }

  if (player->y < 0)
  {
    player->y = 0;
  }
  else if (player->y + player->height > HEIGHT)
  {
    player->y = HEIGHT - player->height;
  }
  if (player->x < 0)
  {
    printf("Erreur : le joueur est sorti de l'écran à gauche\n");
    exit(1);
  }
  else if (player->x + player->width > WIDTH)
  {
    printf("Erreur : le joueur est sorti de l'écran à droite\n");
    exit(1);
  }

  if (player->y < 0)
  {
    printf("Erreur : le joueur est sorti de l'écran en haut\n");
    exit(1);
  }
  else if (player->y + player->height > HEIGHT)
  {
    printf("Erreur : le joueur est sorti de l'écran en bas \n");
    exit(1);
  }
}

