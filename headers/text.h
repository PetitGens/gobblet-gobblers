#ifndef __TEXT_H__
#define __TEXT_H__

enum lang {ENGLISH, FRENCH};

#define LANGUAGE ENGLISH

#if LANGUAGE == ENGLISH

/**Bot Turn Messages**/
#define SIZE_1 "small"
#define SIZE_2 "medium"
#define SIZE_3 "large"

#define BOT_PLACING_MSG "%s placed a %s piece at %s." // (bot_name, size, dest)
#define BOT_MOVING_MSG "%s moved a piece from %s to %s." // (bot_name, src, dest)
/**End of Bot Turn Messages**/

/**TURN.C**/

#define REMAINING "%s's remaining piece(s) :\n"
#define YOUR_TURN "%s, it's your turn !\n\n"

#define RESTART_INDICATION "You can restart your action at any time by pressing entering 'r'.\n"
#define QUIT_INDICATION "Enter 'q' if you want to quit (you'll be asked if you want to save the current game).\n\n"

#define ACTION_INPUT_PROMPT "Enter 'p' to place a piece or 'm' to move a piece :\n>"
#define ACTION_INPUT_ERROR "Please enter 'm' or 'p' !"

#define PAUSE "Press return to continue..."

#define CANCELLED "Action cancelled.\n"

#define BOT_THINKING "It's %s's turn.\n%s is thinking...\n"

#define WINNER "%s is the WINNER !!!\n"

#define PLAY_AGAIN "Do you want to play again ? ('y' or 'n')\n>"

#define SIZE_INPUT_PROMPT "Please enter '1' for a small piece, '2' for a medium piece or '3' for a large piece :\n>"
#define SIZE_INPUT_ERROR "Please enter a valid digit between 1 and 3 !"

#define DEST_INPUT_PROMPT "Please enter the destination place as 'XY', where X is the line and Y is the column :\n>"

#define POS_INPUT_ERROR "Please enter a valid letter followed by a valid digit !"

#define POS_ERROR "Invalid position !"
#define PLACE_SRC_ERROR "You have no more piece of this size left."
#define PLACE_DEST_ERROR "You cannot place this piece here !"

#define SRC_INPUT_PROMPT "Please enter the position of the piece you want to move as 'XY', where X is the line and Y is the column :\n>"

#define MOVE_SRC_ERROR "There is no piece here, or the upper piece on this place is not yours."
#define MOVE_DEST_ERROR "You cannot place this piece here !"

#define EXITING "Exiting game...\n"
#define SAVE_PROMPT "Do you want to save the current game ? (y/n)\n"
#define FILENAME_WRITE_PROMPT "Please enter the name of the file you want to write :\n>"
#define SAVED "Game saved, press return to go back to the main menu..."
/**End of TURN.C*/

#elif LANGUAGE == FRENCH

#define SIZE_1 "petite"
#define SIZE_2 "moyenne"
#define SIZE_3 "grande"

#endif //LANGUAGE

#endif //__TEXT_H__