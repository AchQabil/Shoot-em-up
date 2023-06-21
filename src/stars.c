

#include "../include/stars.h"
#include "../include/game.h"

void stars_init(Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    stars->x[i] = 0;
    stars->y[i] = 0;
    stars->speed[i] = 0;
    stars->active[i] = 0;
    stars->image[i] = NULL;
  }
}


void stars_create_star(Stars *stars, int num_stars)
{
  int created_stars = 0;

  for (int j = 0; j < MAX_STARS; j++)
  {
    if (!stars->active[j])
    {
      if (stars->image[j] == NULL)
      {
        stars->image[j] = MLV_load_image("data/img/star.png");
        if (stars->image[j] == NULL)
        {
          printf("Erreur lors du chargement de l'image\n ");
          exit(1);
        }
        MLV_resize_image_with_proportions(stars->image[j], STAR_WIDTH, STAR_HEIGHT);
      }

      stars->active[j] = 1;
      stars->x[j] = rand() % WIDTH;
      stars->y[j] = 0;
      stars->speed[j] = rand() % 4 + 2;

      created_stars++;
      if (created_stars >= num_stars)
      {
        break;
      }
    }
  }
}

void stars_update(Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (stars->active[i])
    {
      stars->y[i] += stars->speed[i];

      if (stars->y[i] > HEIGHT)
      {
        stars->active[i] = 0;
      }
    }
  }
}

void stars_draw(const Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (stars->active[i])
    {
      MLV_draw_image(stars->image[i], stars->x[i], stars->y[i]);
    }
  }
}

void stars_cleanup(Stars *stars)
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (stars->image[i] != NULL)
    {
      MLV_free_image(stars->image[i]);
      stars->image[i] = NULL;
    }
  }
}