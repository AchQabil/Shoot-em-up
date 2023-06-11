#include "../include/game.h"
#include "../include/menu.h"


void display_menu();


void load_assets(const char *background_image_path, const char *font_path, MLV_Image **image, MLV_Font **font, int font_size)
{
    *image = MLV_load_image(background_image_path);
    if (*image == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de l'image: %s\n", background_image_path);
        exit(1);
    }
    MLV_resize_image(*image, WIDTH, HEIGHT);

    *font = MLV_load_font(font_path, font_size);
    if (*font == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de la police: %s\n", font_path);
        exit(1);
    }
}


void display_instructions()
{
    const char *background_image_path = "data/img/background.jpeg";
    const char *font_path = "data/fonts/Orbitron.ttf";
    const char *title = "Instructions du jeu :";
    const char *instructions1 = "- Utilisez les touches de direction pour déplacer ";
    const char *instructions11 = "votre avion.";
    const char *instructions2 = "- Appuyez sur la touche espace pour tirer et activer";
    const char *instructions22 = " l'arme de base.";
    const char *instructions3 = "- Détruisez les ennemis qui apparaissent sur ";
    const char *instructions33 = "le bord de l'écran.";
    const char *instructions4 = "- Vous disposez de 6 vies.";
    const char *instructions6 = "- Votre score augmente en détruisant des ennemis.";

    MLV_Image *image;
    MLV_Font *font;
    load_assets(background_image_path, font_path, &image, &font, 20);

    while (1)
    {
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_image(image, 0, 0);

        // Espacement avant le titre
        int title_y = 50;

        // Dessiner le titre centré en haut
        int title_width, title_height;
        int title_x = (WIDTH - title_width) / 2;

        // Espacement entre chaque ligne
        int line_height = 60;

        int instructions_x = 20;
        int instructions_y = title_y + title_height + line_height;

        // Dessiner le bouton de retour
        int button_width = 200;
        int button_height = 50;
        int button_x = (WIDTH - button_width) / 2;
        int button_y = HEIGHT - 80;

        int text_width, text_height;
        const char *button_text = "Retour";

        int text_x = button_x + (button_width - text_width) / 2;
        int text_y = button_y + (button_height - text_height) / 2;

        // On attend une entrée de l'utilisateur
        int mouse_x, mouse_y;

        MLV_get_size_of_text(title, &title_width, &title_height);

        MLV_draw_text_with_font(title_x, title_y, title, font, MLV_COLOR_WHITE);
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions1, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions11, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions2, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions22, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions3, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions33, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions4, font, MLV_COLOR_WHITE);
        instructions_y += line_height;
        MLV_draw_text_with_font(instructions_x, instructions_y, instructions6, font, MLV_COLOR_WHITE);

        MLV_draw_filled_rectangle(button_x, button_y, button_width, button_height, MLV_COLOR_GRAY);
        MLV_get_size_of_text(button_text, &text_width, &text_height);

        MLV_draw_text_with_font(text_x, text_y, button_text, font, MLV_COLOR_BLACK);
        MLV_actualise_window();

        MLV_get_mouse_position(&mouse_x, &mouse_y);

        // On traite l'entrée
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
            mouse_x >= button_x && mouse_x < button_x + button_width &&
            mouse_y >= button_y && mouse_y < button_y + button_height)
        {
            display_menu();
            break;
        }

        MLV_wait_seconds(0.1);
    }

    MLV_free_font(font);
}

void display_menu()
{

    const char *background_image_path = "data/img/background.jpeg";
    const char *font_path = "data/fonts/Orbitron.ttf";
    char *result = "";

    MLV_Image *image;
    MLV_Font *font;
    load_assets(background_image_path, font_path, &image, &font, 30);

    MLV_draw_text_with_font(30, 30, result, font, MLV_COLOR_WHITE);

    while (1)
    {
        // On dessine le menu
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_image(image, 0, 0);
        result = " Game Shoot'em up | ESIPE Info 1";
        MLV_draw_text_box_with_font(
            10, 10, WIDTH - 20, 60,
            result, font,
            30, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

        int max_width = 0;
        int temp_width, temp_height;
        result = "Press P to play        ";
        MLV_get_size_of_adapted_text_box(result, 30, &temp_width, &temp_height);
        if (temp_width > max_width)
            max_width = temp_width;

        result = "Press I for instructions";
        MLV_get_size_of_adapted_text_box(result, 30, &temp_width, &temp_height);
        if (temp_width > max_width)
            max_width = temp_width;

        result = "Press ESCAPE to quit    ";
        MLV_get_size_of_adapted_text_box(result, 30, &temp_width, &temp_height);
        if (temp_width > max_width)
            max_width = temp_width;

        MLV_draw_adapted_text_box_with_font(100, HEIGHT / 2 - 100 - temp_height / 2, "       Press P to play        ", font, 20, MLV_COLOR_GREEN, MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_TEXT_LEFT);
        MLV_draw_adapted_text_box_with_font(100, HEIGHT / 2 - temp_height / 2 + 30, "Press I for instructions", font, 20, MLV_COLOR_YELLOW, MLV_COLOR_BLACK, MLV_COLOR_YELLOW, MLV_TEXT_LEFT);
        MLV_draw_adapted_text_box_with_font(100, HEIGHT / 2 + 100 - temp_height / 2 + 30 * 2, "Press ESCAPE to quit  ", font, 20, MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_TEXT_LEFT);

        MLV_actualise_window();

        MLV_Keyboard_button button;
        MLV_wait_keyboard(&button, NULL, NULL);

        switch (button)
        {
        case MLV_KEYBOARD_p:
            return;
        case MLV_KEYBOARD_i:
            display_instructions();
            return;

        case MLV_KEYBOARD_ESCAPE:
            exit(0);
        default:
            break;
        }
    }

    MLV_free_font(font);
}
