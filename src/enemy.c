#include "../include/enemy.h"
#include <stdio.h>

void enemy_init(Enemy *enemy, int x, int y, int dx, int dy, int width,
                int height, MLV_Image *image) {
  enemy->x = x;
  enemy->y = y;
  enemy->dx = dx;
  enemy->dy = dy;
  enemy->width = width;
  enemy->height = height;
  enemy->active = 0; // Les ennemis sont initialisés comme étant inactifs
  enemy->image = image;
}

void enemy_activate(Enemy *enemy) { enemy->active = 1; }

void enemy_deactivate(Enemy *enemy) { enemy->active = 0; }

void enemy_set_speed(Enemy *enemy, int dx, int dy) {
  enemy->dx = dx;
  enemy->dy = dy;
}

void enemy_update_position(Enemy *enemy) {
  // Mettre à jour la position de l'ennemi en fonction des variations dx et dy
  enemy->x += enemy->dx;
  enemy->y += enemy->dy * 2; // Vitesse verticale doublée
}

void enemy_draw(const Enemy *enemy, const MLV_Image *sprite) {
  // Dessiner l'ennemi à sa position actuelle en utilisant l'image du sprite
  MLV_draw_image(sprite, enemy->x, enemy->y);
}

void enemy_list_update(Enemy *enemies, int count) {
  for (int i = 0; i < count; i++) {
    Enemy *enemy = &enemies[i];
    if (enemy->active) {
      enemy_update_position(enemy);
    }
  }
}

void enemy_list_draw(const Enemy *enemies, const MLV_Image *sprite, int count) {
  for (int i = 0; i < count; i++) {
    const Enemy *enemy = &enemies[i];
    enemy_draw(enemy, sprite);
  }
}

int enemy_list_is_empty(const Enemy *enemies, int count) {
  for (int i = 0; i < count; i++) {
    const Enemy *enemy = &enemies[i];
    if (enemy->active) {
      return 0; // L'ennemi actif a été trouvé, la liste n'est pas vide
    }
  }
  return 1; // Tous les ennemis sont inactifs, la liste est vide
}