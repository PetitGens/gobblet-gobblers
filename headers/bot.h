#ifndef __BOT_H__
#define __BOT_H__

#include "board.h"
#include "action.h"


typedef enum {EASY, MEDIUM_DIFF, HARD} bot_difficulty_e; 

void bot_play(board game, player bot_player_num, bot_difficulty_e bot_dif, char bot_name[], char turn_message[]);

void bot_easy(board game, player bot_player_num,  enum action_e* p_action, int input1[2], int input2[2]);

void random_action(board game, player bot_player_num, enum action_e* p_action, int input1[2], int input2[2]);

void random_place(board game, int* p_size, int dest[2]);

void random_move(board game, int src[2], int dest[2]);

#endif //__BOT_H__