#include "MLV/MLV_all.h"
#include "include/game.h"
#include "include/graphics.h"
#include "include/stars.h"

#include "include/collision.h"
#include <stdbool.h>

#define FRAME_TIME (1.0 / 48.0) // Durée cible d'une frame en secondes

int main() {
  Game game;
  int quit = 0;
  int last_time, new_time, elapsed_time;

  // Initialiser le jeu
  init_game(&game);

  int star_creation_counter = 0;

  // Boucle principale du jeu
  while (!quit) {
    // Récupérer le temps au début de la frame
    last_time = MLV_get_time();

    // Afficher la frame
    graphics_clear();
    draw_game(&game);
    graphics_update();
    
    // Résoudre les événements
    handle_input_game(&game, &quit);

    // Mouvements des entités sur le plateau
    update_game(&game);
    
     // Résolutions des collisions
    game_handle_collision(&game);

    // Récupérer le temps à la fin de la frame
    new_time = MLV_get_time();

    // Calculer le temps écoulé pour la frame
    elapsed_time = new_time - last_time;

    // Attendre si la frame était trop courte
    if (elapsed_time < (FRAME_TIME * 1000)) {
      int wait_time = (int)((FRAME_TIME * 1000) - elapsed_time);
      MLV_wait_milliseconds(wait_time);
    }

    if (star_creation_counter >= 50) {
      stars_create_star(&game.stars, 20);
      star_creation_counter = 0;
    }

    star_creation_counter++;
  }
  
  // Nettoyer et fermer la fenêtre graphique
  clean_game(&game);

  return 0;
}
