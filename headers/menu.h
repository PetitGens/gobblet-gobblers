#ifndef __MENU_H__
#define __MENU_H__

#include "board.h"

/**
 * \file menu.h
 * 
 * \brief functions that consist of menus giving the player access to every game functionalities
 * 
 * \authors Julien AIT AZZOUZENE, Ewan CANTON
 * 
*/

typedef enum {UKNOWN, HELP, PVP, LOAD_PVP, PVB, LOAD_PVB, QUIT, LEADERBOARD} menu_choice;

void main_menu();

void main_help();

void menu_start_pvb();

void leaderboard();

#endif //__MENU_H__