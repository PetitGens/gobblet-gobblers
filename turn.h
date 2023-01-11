#ifndef TURN_H
#define TURN_H

#include "board.h"

/**
 * @file turn.h
 * 
 * @brief essential functions for the working of the game
 * 
 * This file contains essential functions that permitts to play your turn, check if there is a winner
 * 
 * @authors Julien AIT AZZOUZENE, Ewan CANTON
 */

/**
 * @brief defines what a player can do, to place, to move or both
 */
enum possible_e {ANY, PLACE_ONLY, MOVE_ONLY};


/**
 * @brief the function that is called at each mainloop iteration
 * 
 * This funtions, displays the game interface, and give the player the choice of the action
 * (if he actually has the choice).
 * 
 * @param game the board in use
 * @param player1_name 
 * @param player2_name
 * 
 * @return returns 1 only if the players want to exit the game, else returns 0
 */
int turn(board game, char player1_name[], char player2_name[]);

/**
 * @brief displays an message to warn the player he made a mistake
 * 
 * This functions simply prints a message, and then wait for an action from the player.
 * It does not raise an actual error that stops the programm.
 * 
 * @param message -> the message to display
 */
void error_message (const char message[]);


/**
 * @brief displays the winner if there is one, and ask if the players want to play again
 * 
 * The functions uses a board pointer because we may have to create a new board
 * (and since this is a main local variable, we need to pass it by address)
 * 
 * @param p_game -> a pointer to the board in use
 * @param player1_name
 * @param player2_name 
 * @return int -> returns 1 if no one won or if the players want to play again ; else returns 0
 */
int declare_winner(board* p_game, char player1_name[], char player2_name[]);

/**
 * @brief check if the current player can place, move or do any of the two actions
 * 
 * @param game -> the board in use
 * @param current_player -> the player whose the turn is
 * @return enum possible_e -> the action the player can make
 */
enum possible_e determine_possible_action(board game, player current_player);


/**
 * @brief tries to place a piece on the board, asking the player for the size and target position
 * 
 * @param game -> the board in use
 * @return int -> returns 1 if the placement was successful, 2 if the player wants to cancel its action,
 *             -> 3 if the player wants to exit the game, and 0 if the move is invalid
 */
int place (board game);


/**
 * @brief tries to move a piece of the board, asking the player for the source and target positions
 * 
 * @param game -> the board in use
 * @return int -> returns 1 if the move was successful, 2 if the player wants to cancel its action,
 *             -> 3 if the player wants to exit the game, and 0 if the move is invalid
 */
int move (board game);

void exit_game(board game);

#endif //TURN_H
