#ifndef __RATING_H__
#define __RATING_H__

#include "input.h"

#define MAX_NB_RATINGS 200

typedef struct
{
    char player_name[NAME_MAX_LENGTH];
    int score;
    bool exists_in_file;
} rating;

void load_ratings(rating players_ratings[2]);

void save_rating(rating* p_rat);

void calculate_ratings(rating* p_winner, rating* p_loser);

int load_all_ratings(rating ratings[MAX_NB_RATINGS]);

void sort_all_ratings(rating ratings[MAX_NB_RATINGS], int nb_ratings);

#endif //__RATING_H__