#ifndef __TEXT_H__
#define __TEXT_H__

#define TEXT_MAX_SIZE 128

#define ENGLISH 0
#define FRENCH 1


//enum lang {ENGLISH, FRENCH};

#define LANGUAGE FRENCH

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
#define MOVE_DEST_ERROR "You cannot move this piece here !"

#define EXITING "Exiting game...\n"
#define SAVE_PROMPT "Do you want to save the current game ? (y/n)\n"
#define FILENAME_WRITE_PROMPT "Please enter the name of the file you want to write :\n>"
#define SAVED "Game saved, press return to go back to the main menu..."
/**End of TURN.C**/

/**INPUT.C**/

#define NAME_INPUT_PROMPT "Please enter your name.\n>"
#define FIRST_NAME_INPUT_PROMPT "Please enter the first player's name.\n>"
#define SECOND_NAME_INPUT_PROMPT "Please enter the second player's name.\n>"

/**End of INPUT.C**/

/**GAMELOOP.C**/

#define FILENAME_INPUT_PROMPT "Please enter the save file name >"
#define FILE_OPENING_ERROR "The file cannot be opened, or its format is incorrect."

/**End of GAMELOOP.C**/

/**MENU.C**/

#define GAME_TITLE "Gobblet Gobbers main menu :\n\n"

#define MENU_INTRO "Enter 'pvp' to start a 2 players game.\nEnter 'help' for other commands.\n\n"

#define GAME_EXITING "Exiting game program.\n"

#define UNKNOWN_COMMAND "unknown command\n"

/**HELP MESSAGES**/

#define ALL_COMMANDS "\nAll commands :\n\n"

#define HELP_BVB "- bvb : starts a game between 2 bots\n"
#define HELP_HELP "- help : displays this text\n"
#define HELP_LEADERBOARD "- leaderboard : displays a leaderboard stored in rating.dat (if the file exists)\n"
#define HELP_LOAD_PVB "- load-pvb : loads a game against a bot previously saved\n"
#define HELP_LOAD_PVP "- load-pvp : loads a 2 players game previously saved\n"
#define HELP_PVB "- pvb : starts a game against a bot\n"
#define HELP_PVP "- pvp : starts a 2 players game\n"
#define HELP_QUIT "- quit : exits the game program\n"

/**End of END MESSAGES**/

#define RETURN_MAIN_MENU "Press return to get back to the main menu..."

#define DIFFICULTY_INPUT_PROMPT "Please choose bot difficulty (1 for easy, 2 for medium, 3 for hard) : "
#define DIFFICULTY_INPUT_ERROR "Invalid input, press return to get back to the main menu..."
#define FIRST_DIFFICULTY_INPUT_PROMPT "Please choose the first bot's difficulty (1 for easy, 2 for medium, 3 for hard) : "
#define SECOND_DIFFICULTY_INPUT_PROMPT "Please choose the second bot's difficulty (1 for easy, 2 for medium, 3 for hard) : "

/**End of MENU.C**/

#elif LANGUAGE == FRENCH

/**Bot Turn Messages**/
#define SIZE_1 "petite"
#define SIZE_2 "moyenne"
#define SIZE_3 "grande"

#define BOT_PLACING_MSG "%s a placé une %s pièce en %s." // (bot_name, size, dest)
#define BOT_MOVING_MSG "%s a déplacé une pièce de %s vers %s." // (bot_name, src, dest)
/**End of Bot Turn Messages**/

/**TURN.C**/

#define REMAINING "Pièces restantes pour %s :\n"
#define YOUR_TURN "%s, c'est votre tour !\n\n"

#define RESTART_INDICATION "Vous pouvez recommencer votre action à tout moment à saisissant 'r'.\n"
#define QUIT_INDICATION "Saisissez 'q' pour arrêter la partie (vous pourrez alors la sauvegarder).\n\n"

#define ACTION_INPUT_PROMPT "Saisissez 'p' pour placer ou 'm' pour déplacer une pièce :\n>"
#define ACTION_INPUT_ERROR "Veuillez saisir 'p' ou 'm' !"

#define PAUSE "Appuyez sur Entrée pour continuer..."

#define CANCELLED "Action annulée.\n"

#define BOT_THINKING "C'est au tour de %s.\n%s réfléchit...\n"

#define WINNER "%s a GAGNÉ !!!\n"

#define PLAY_AGAIN "Voulez-vous rejouer ? ('y' pour \"oui\" / 'n' pour \"non\")\n>"

#define SIZE_INPUT_PROMPT "Saisissez '1' pour une petite pièce, '2' pour une moyenne, ou '3' pour une grande :\n>"
#define SIZE_INPUT_ERROR "Veuillez saisir un nombre valide entre 1 et 3 !"

#define DEST_INPUT_PROMPT "Saisissez la case de destination en tant que XY, où X est la ligne et Y la colonne :\n>"
#define POS_INPUT_ERROR "Veuillez saisir une lettre et un chiffres valides !"

#define POS_ERROR "Position invalide !"
#define PLACE_SRC_ERROR "Vous n'avez plus de pièce de cette taille !"
#define PLACE_DEST_ERROR "Vous ne pouvez pas placer cette pièce ici !"

#define SRC_INPUT_PROMPT "Saisissez la case où se trouve la pièce à déplacer en tant que XY, où X est la ligne et Y la colonne :\n>"
#define MOVE_SRC_ERROR "Il n'y a pas de pièce ici, ou elle n'est pas à vous !"
#define MOVE_DEST_ERROR "Vous ne pouvez pas déplacer cette pièce ici !"

#define EXITING "Arrêt de la partie...\n"
#define SAVE_PROMPT "Voulez-vous sauvegarder cette partie pour la reprendre plus tard ? (y/n)\n"
#define FILENAME_WRITE_PROMPT "Veuillez saisir le nom du fichier que vous voulez créer :\n>"
#define SAVED "La partie a été sauvegardée. Appuyer sur Entrée pour retourner au menu principal..."
/**End of TURN.C**/

/**INPUT.C**/

#define NAME_INPUT_PROMPT "Saisissez votre nom.\n>"
#define FIRST_NAME_INPUT_PROMPT "Saisissez le nom du premier joueur.\n>"
#define SECOND_NAME_INPUT_PROMPT "Saisissez le nom du deuxième joueur.\n>"

/**End of INPUT.C**/

/**GAMELOOP.C**/

#define FILENAME_INPUT_PROMPT "Veuillez saisir le nom du fichier de sauvegarde : >"
#define FILE_OPENING_ERROR "Le fichier n'a pas pu être ouvert, ou son format est incorrect"

/**End of GAMELOOP.C**/

/**MENU.C**/

#define GAME_TITLE "Gobblet Gobbers ; menu principal :\n\n"

#define MENU_INTRO "Saisissez 'pvp' pour démarrer une partie entre deux joueurs.\nSaisissez 'help' pour voir les autres commandes.\n\n"

#define GAME_EXITING "Arrêt du programme.\n"

#define UNKNOWN_COMMAND "commande inconnue\n"

/**HELP MESSAGES**/

#define ALL_COMMANDS "\nToutes les commandes :\n\n"

#define HELP_BVB "- bvb : démarre une partie entre deux joueurs ordinateurs\n"
#define HELP_HELP "- help : affiche ce texte\n"
#define HELP_LEADERBOARD "- leaderboard : affiche un classement stocké dans le fichier rating.dat (si il existe)\n"
#define HELP_LOAD_PVB "- load-pvb : charge une partie contre un joueur ordinateur précédemment sauvegardée\n"
#define HELP_LOAD_PVP "- load-pvp : charge une partie entre deux joueurs précédemment sauvegardée\n"
#define HELP_PVB "- pvb : démarre une partie contre un joueur ordinateur\n"
#define HELP_PVP "- pvp : démarre une partie entre deux joueurs\n"
#define HELP_QUIT "- quit : arrête le programme\n"

/**End of END MESSAGES**/

#define RETURN_MAIN_MENU "Appuyer sur Entrée pour retourner au menu principal..."

#define DIFFICULTY_INPUT_PROMPT "Saisissez le niveau de difficulté (1 pour facile, 2 pour moyen, 3 difficile) : "
#define DIFFICULTY_INPUT_ERROR "Saisie invalide, appuyer sur Entrée pour retourner au menu principal..."
#define FIRST_DIFFICULTY_INPUT_PROMPT "Saisissez le niveau de difficulté du premier joueur ordinateur (1 pour facile, 2 pour moyen, 3 difficile) : "
#define SECOND_DIFFICULTY_INPUT_PROMPT "Saisissez le niveau de difficulté du deuxième joueur ordinateur (1 pour facile, 2 pour moyen, 3 difficile) : "

/**End of MENU.C**/

#endif //LANGUAGE

#endif //__TEXT_H__