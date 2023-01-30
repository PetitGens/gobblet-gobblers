# Gobblet-Gobblers

This program is a digital version of Gobblet Gobblers (a Tic-Tac-Toe like board game).  
It was made in C during my IT studies at Caen for a learning project.
After the end of this project, I continued enhancing the game during my free time.

Currently, the game only has a CLI (Command Line Interface) and is only runnable on Linux, due to the use of colored text that cmd et Powershell from Windows don't offer. 

## Rules of the game

The this game's rules are very similar to Tic Tac Toe's, with some additions :
* Each player has pieces of different sizes : SMALL, MEDIUM and HARD.
* The players have limited pieces (2 for each size).
* A piece can be placed over another if it is strictly bigger.
* You can place pieces on the board, but you can also move one of your pieces that are already on it.

The goal is the same as Tic Tac Toe's : to align 3 pieces of your color.

If the two players happen to fulfill the winning condition at the same time, the game will continue until only one player can win.

## How to launch the game

1 Download the repository as a zip (Code > Download ZIP).

2 Open a terminal in the game folder (right click > "open in terminal" in file explorer).

3 Compile the code using `$make` (only for the first time).

4 Launch the game executable : `$./gobblet`.

## How to play

### Main menu

Upon opening the game, a menu will display letting you choose a game function :

* `help` -> displays a list of all available functions
* `pvp` -> starts a game between two human players
* `pvb` -> starts a game against a bot player (i.e controlled by the computer)
* `bvb` -> starts a game between two bot players (not very useful, I used that mainly for debugging)
* `load-pvp` / load-pvb -> loads a game previously saved (can be a pvp or a pvb game ; see Game saving section for more details)
* `leaderboard` -> displays a leaderboard based on the ELO system ; it is automatically updated after pvp games and stored in a `rating.dat` file.
* `quit` -> exits the game program

### Game progress

Before the game starts, you have to enter the players' name (for human players) and / or bot difficulty (between 1 and 3).
During each turn, you can either place, move or quit the game (in this case, you'll be prompted to save the current game).
You can also restart a turn by pressing 'r'.

#### Placing a piece

In order to place a piece, you must type the letter ‘P’ as a first input (if you are asked to choice between placing and moving). Then you must input a digit between 1 and 3 for the size. Finally, you must input the position where you want to place your piece. To do so, type a letter for the row (“A”, “B” or “C”) and a digit for the column (1, 2 or 3).

![placing a piece](/screenshots/placing.png)

If your action is valid, the placement will be achieved and the other player will be able to play.
Else, you will have to play your turn again.

![error while trying to place a piece](/screenshots/placing_error.png)

#### Moving a piece

In order to move a piece, you must type the letter ‘M’ as a first input (if you are asked to choice between placing and moving). Then you have to input two positions, the one where you piece is located and the one onto you want to move this piece. To input a position, type a letter for the row (“A”, “B” or “C”) and a digit for the column (1, 2 or 3).

![moving a piece](/screenshots/moving.png)

If your action is valid, the movement will be achieved and the other player will be able to play.
Else, you will have to play your turn again.

![error while trying to move a piece](/screenshots/moving_error.png)

#### Quiting

In order to quit the current game, press 'Q'. You can then save the game if you want to resume it later (see Game saving section for more details).

### Game saving

You can save games upon exiting, you are then asked for the filename (you can use whatever extension you want, `.sav` is recommanded). Even if the save is a simple text file, it is not supposed to be edited by the user.
