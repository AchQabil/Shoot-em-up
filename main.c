#include "MLV/MLV_all.h"
#include "include/game.h"
#include "include/stars.h"
#include "include/explosion.h"
#include "include/menu.h"
#include "include/collision.h"

#define FRAME_TIME (1.0 / 48.0) // Durée cible d'une frame en secondes

int main()
{
  Game game;
  bool quit = false;
  int last_time, new_time, elapsed_time;

  MLV_create_window("Game", "Game", WIDTH, HEIGHT);
  const char *sound_file_path = "data/sounds/sound_game.wav";

  // Initialise l'infrastructure son de la librairie MLV.
  if (MLV_init_audio())
  {
    fprintf(
        stderr,
        "L'infrasctructure audio de la librairie MLV ne s'est pas \
correctement initialisé.");
    exit(1);
  }

  game.game_sound = MLV_load_sound(sound_file_path);
  MLV_play_sound(game.game_sound, 1.0);

  // Affiche le menu
  display_menu();
  MLV_free_window();

  // Initialiser le jeu
  init_game(&game);

  int star_creation_counter = 0;

  // Boucle principale du jeu
  while (!quit)
  {

    // Récupérer le temps au début de la frame
    last_time = MLV_get_time();

    // Afficher la frame
    MLV_clear_window(MLV_COLOR_BLACK);
    draw_game(&game);

    MLV_update_window();
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
    if (elapsed_time < (FRAME_TIME * 1000))
    {
      int wait_time = (int)((FRAME_TIME * 1000) - elapsed_time);
      MLV_wait_milliseconds(wait_time);
    }

    if (star_creation_counter >= 50)
    {
      stars_create_star(&game.stars, 20);
      star_creation_counter = 0;
    }

    star_creation_counter++;
  }

  // Arrêter la lecture du son et nettoyer le jeu
  clean_game(&game);

  return 0;
}
