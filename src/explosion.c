#include "../include/explosion.h"

void explosion_init(Explosion *explosion, int x, int y) {
    explosion->x = x;
    explosion->y = y;
    explosion->active = false;
    explosion->start_time = 0;
    explosion->current_image = 0;
    explosion->width = EXPLOSION_WIDTH;
    explosion->height = EXPLOSION_HEIGHT;

    // Initialiser le tableau d'images de l'explosion
    for (int i = 0; i < NUM_EXPLOSION_IMAGES; i++) {
        char filename[30];
        sprintf(filename, "data/img/explosion%d.png", i);
        explosion->images[i] = MLV_load_image(filename);
        if (explosion->images[i] == NULL) {
            printf("Erreur lors du chargement de l'image d'explosion %d\n", i);
            exit(1);
        }
        MLV_resize_image(explosion->images[i], EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
    }
}


void explosion_activate(Explosion *explosion, int x, int y) {
    explosion->active = true;
    explosion->x = x;
    explosion->y = y;
    explosion->start_time = MLV_get_time();
}

void explosion_draw(const Explosion *explosion) {
    if (explosion->active) {
        if (explosion->current_image < 0 || explosion->current_image >= NUM_EXPLOSION_IMAGES) {
            printf("Erreur : current_image est hors limites.\n");
            return;
        }
        if (explosion->images[explosion->current_image] == NULL) {
            printf("Erreur : images[current_image] est NULL.\n");
            return;
        }
        MLV_draw_image(explosion->images[explosion->current_image], explosion->x, explosion->y);
    }
}

void explosion_update(Explosion *explosion) {
    if (explosion->active && MLV_get_time() - explosion->start_time > EXPLOSION_DURATION) {
        explosion->active = false;
    }
    else if (explosion->active) {
        explosion->current_image = (explosion->current_image + 1) % NUM_EXPLOSION_IMAGES;
    }
}

void explosion_cleanup(Explosion *explosions) {
    for (int i = 0; i < NUM_EXPLOSION_IMAGES; i++) {
        if (explosions[i].images[i] != NULL) {
            MLV_free_image(explosions[i].images[i]);
            explosions[i].images[i] = NULL;
        }
    }
}