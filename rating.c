#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rating.h"
#include "board.h"

void load_ratings(rating players_ratings[2])
{
    players_ratings[0].score = 0;
    players_ratings[1].score = 0;

    FILE* stream = fopen("rating.dat", "r");
    if (stream != NULL)
    {
        char input[NAME_MAX_LENGTH];
        int mode = 0;
        bool player1_found = false, player2_found = false;

        while ( fgets(input, NAME_MAX_LENGTH - 1, stream) != NULL && (players_ratings[0].score == 0 || players_ratings[1].score == 0) )
        {
            delete_carriage_return(input);
            if (mode == 1)
            {
                int score = atoi(input);
                if (score != 0)
                {
                    if (player1_found)
                        players_ratings[0].score = score;
                    else if (player2_found)
                        players_ratings[1].score = score;
                    mode = 2;
                }
                else
                    mode = 0;
                player1_found = false;
                player2_found = false;
            }
            if (mode == 0 )
            {
                if (strcmp(input, players_ratings[0].player_name) == 0 && players_ratings[0].score == 0)
                {
                    player1_found = true;
                    mode = 1;
                }
                else if (strcmp(input, players_ratings[1].player_name) == 0 && players_ratings[1].score == 0)
                {
                    player2_found = true;
                    mode = 1;
                }
            }
            else if (mode == 2)
                mode = 0;
        }
        
        fclose(stream);

        if (players_ratings[0].score > 0)
            players_ratings[0].exists_in_file = true;
        else
        {
            players_ratings[0].exists_in_file = false;
            players_ratings[0].score = 1000;
            save_rating(&players_ratings[0]);
        }

        if (players_ratings[1].score > 0)
            players_ratings[1].exists_in_file = true;
        else
        {
            players_ratings[1].exists_in_file = false;
            players_ratings[1].score = 1000;
            save_rating(&players_ratings[1]);
        }
    }
    else
    {
        if (players_ratings[0].score > 0)
            players_ratings[0].exists_in_file = true;
        else
        {
            players_ratings[0].exists_in_file = false;
            players_ratings[0].score = 1000;
            save_rating(&players_ratings[0]);
        }

        if (players_ratings[1].score > 0)
            players_ratings[1].exists_in_file = true;
        else
        {
            players_ratings[1].exists_in_file = false;
            players_ratings[1].score = 1000;
            save_rating(&players_ratings[1]);
        }
    }
}

void save_rating(rating* p_rat)
{
    if (p_rat->exists_in_file)
    {
        FILE* stream = fopen("rating.dat", "r+");

        char input[NAME_MAX_LENGTH];
        bool found = false;

        while( fgets(input, NAME_MAX_LENGTH - 1, stream) != NULL && found == false)
        {
            delete_carriage_return(input);
            if (strcmp(input, p_rat->player_name) == 0)
            {
                fprintf(stream, "%5d\n", p_rat->score);
                found = true;
            }
        }
        fclose(stream);
    }
    else
    {
        FILE* stream = fopen("rating.dat", "a");
        fprintf(stream, "%s\n", p_rat->player_name);
        fprintf(stream, "%5d\n", p_rat->score);
        p_rat->exists_in_file = true;
        fclose(stream);
    }
}

void calculate_ratings(rating* p_winner, rating* p_loser)
{
    p_winner->score += 10;
    p_loser->score -= 8;
    if (p_loser->score < 1000)
        p_loser->score = 1000;
}

int load_all_ratings(rating ratings[MAX_NB_RATINGS])
{
    FILE* stream = fopen("rating.dat", "r");
    if (stream != NULL)
    {
        char input[NAME_MAX_LENGTH];
        int mode = 0;
        int i = 0;

        while (fgets(input, NAME_MAX_LENGTH - 1, stream) != NULL)
        {
            delete_carriage_return(input);
            if (mode == 1)
            {
                int score = atoi(input);
                if (score != 0)
                {
                    ratings[i].score = score;
                    mode = 2;
                }
                else
                    mode = 0;
                i++;
            }
            if (mode == 0 )
            {
                if (input[0] != '\0')
                {
                    strcpy(ratings[i].player_name, input);
                }
                mode = 1;
            }
            else if (mode == 2)
                mode = 0;
        }
        
        fclose(stream);
        return i;
    }

    return 0;
}

void sort_all_ratings(rating ratings[MAX_NB_RATINGS], int nb_ratings)
{
    int i_max;
    for (int i = 0; i < (nb_ratings-1); i++)
    {
        i_max = i;
    
        for (int j=i + 1; j < nb_ratings; j++)
        {
        if (ratings[i_max].score < ratings[j].score)
            i_max = j;
        }
        if (i_max != i)
        {
        rating tmp = ratings[i];
        ratings[i] = ratings[i_max];
        ratings[i_max] = tmp;
        }
    }
}