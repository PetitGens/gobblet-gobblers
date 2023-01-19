#ifndef __GAMELOOP_H__
#define __GAMELOOP_H__

#include "board.h"

/**
 * \file gameloop.h
 * 
 * \brief gameloops functions for Gobblet game
 * 
 * The functions contained in this file correspond to every possible game variant (player vs player, player vs ai, ai vs ai)
 * 
 * \authors Julien AIT AZZOUZENE, Ewan CANTON
 * 
*/

void pvp_loop(board game);

void pvp_start();

void pvp_load();

#endif //__GAMELOOP_H__