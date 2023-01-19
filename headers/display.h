#ifndef DISPLAY_H
#define DISPLAY_H

#include "board.h"
#include "rating.h"

/**
 * \file display.h
 *
 * \brief functions relatives to display for Gobblet game
 *
 * This file contains the main functions used for the display of the game
 *  
 * \authors Julien AIT AZZOUZENE, Ewan CANTON
 *
 */


/**
 * @brief all text colors available for a terminal
 */
enum color_e {BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};

/**
 * @brief clears the shell in use
 * 
 * Give the same result as system('clear'), without using system().
 * 
 */
void clear_screen();


/**
 * @brief changes the color of the text in standart output
 * The effect lasts until the color is changed again or resetted.
 * @param game -> the color you want for the text 
 */
void change_output_color(enum color_e color);

/**
 * @brief resets the color of the text in standart output
 */
void reset_output_color();

/**
 * @brief displays the game board
 * Displays the game board with all its pieces in different sizes and color.
 * The color of a piece depends on its player.
 * @param game -> the board in use
 */
void print_board(board game);


/**
 * @brief insert the correct character for the piece in given position
 * 
 * We have to use a character string because the character can take more than one byte,
 * and thus cannot be placed in a 'char'.
 * 
 * @param piece -> character string where the character is inserted
 * @param game -> the board in use
 * @param line } -> the position of the piece 
 * @param col  }
 */
void insert_piece(char piece[], board game, int line, int col);

void print_leaderboard(rating ratings[MAX_NB_RATINGS], int nb_ratings);

void format_name_for_leaderboard(char name[NAME_MAX_LENGTH]);

#endif //DISPLAY_H
