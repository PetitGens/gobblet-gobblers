#ifndef INPUT_H
#define INPUT_H

#include "board.h"
#include "menu.h"

#define NAME_MAX_LENGTH 30
#define CHOICE_MAX_LENGTH 30
#define FILENAME_MAX_LENGTH 30

/**
 * @file input.h
 * 
 * @brief all functions that imply an input of the user
 * 
 * @authors Julien AIT AZZOUZENE, Ewan CANTON
 */

/**
 * @brief ask the players to input their names
 * 
 * @param name1 
 * @param name2 
 */
void input_players_names(char name1[], char name2[]);


/**
 * @brief delete the first carriage in the end of a char string
 * 
 * This function cuts the string just before the first '\n' character seen
 * 
 * @param string
*/
void delete_carriage_return (char string[]);

/**
 * @brief action chosen by the player
 * 
 * ERROR stands for an invalid input from the player
*/
enum action_e {ERROR, PLACE, MOVE, EXIT};

/**
 * @brief asks to the player the action he wants to do
 * 
 * @return the chosen action, equals ERROR if invalid input
*/
enum action_e input_place_move();

/**
 * @brief asks to the player the size of the piece he wants to place
 * 
 * @return the chosen size, equals NONE (0) if invalid input
 *         returns CANCEL_SIZE if the players input 'R'
 *         returns EXIT_SIZE if the player inputs 'Q'
*/
size input_piece_size();

/**
 * @brief asks the player for a position on the board
 * 
 * The position is stored on *p_line and *p_col.
 * If the number of line / column is invalid, the corresponding variable will equals -1
 * If the player inputs 'R', the line will equal -2
 * If the player inputs 'Q', the column will equal -2
 * 
 * @param p_line a pointer to the number of the line in wich the player wants to place a piece
 * @param p_col a pointer to the number of the column in wich the player wants to place a piece
*/
void input_position (int* p_line, int* p_col);

/**
 * @brief asks the player to answer yes or no
 * 
 * @return 1 for "yes", 0 for "no", -1 if if the player answers something else
*/
int input_yes_no();

menu_choice input_main_menu();

void input_filename(char filename[FILENAME_MAX_LENGTH]);

#endif //INPUT_H
