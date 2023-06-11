#ifndef MENU_H
#define MENU_H

#include "MLV/MLV_all.h"

/**
 * @brief Affiche le menu principal du jeu.
 *
 * Cette fonction est responsable de la création et de l'affichage du menu principal du jeu.
 * Dans ce menu, l'utilisateur peut choisir de commencer le jeu, de visualiser les instructions
 * ou de quitter le jeu. Cette fonction prend en charge la gestion des événements d'entrée
 * utilisateur dans le menu principal.
 *
 */
void display_menu();

/**
 * @brief Affiche les instructions du jeu.
 *
 * Cette fonction est responsable de la création et de l'affichage des instructions du jeu.
 * L'utilisateur peut accéder à cette vue à partir du menu principal. Cette fonction prend
 * en charge la gestion des événements d'entrée utilisateur dans la vue des instructions.
 */
void display_instructions();

#endif // MENU_H
