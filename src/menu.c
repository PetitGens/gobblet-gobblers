#include <stdio.h>

#include "../headers/board.h"
#include "../headers/menu.h"
#include "../headers/input.h"
#include "../headers/display.h"
#include "../headers/gameloop.h"
#include "../headers/bot.h"
#include "../headers/text.h"

void main_menu()
{
    bool running = true;
    bool display_intro = true;

    while(running)
    {
        if (display_intro)
        {
            clear_screen();

            _printf(GAME_TITLE);

            _printf(MENU_INTRO);

            display_intro = false;
        }

        _printf(">");
        menu_choice input = input_main_menu();

        switch(input)
        {
            case HELP:
                main_help();
                break;
            case PVP:
                pvp_start();
                display_intro = true;
                break;
            case LOAD_PVP:
                pvp_load();
                display_intro = true;
                break;
            case PVB:
                menu_start_pvb();
                display_intro = true;
                break;
            case LOAD_PVB:
                menu_load_pvb();
                display_intro = true;
                break;
            case BVB:
                menu_start_bvb();
                display_intro = true;
                break;
            case QUIT:
                _printf(GAME_EXITING);
                running = false;
                break;
            case LEADERBOARD:
                leaderboard();
                display_intro = true;
                break;
            default:
                _printf(UNKNOWN_COMMAND);
        }
    }
}

void main_help()
{
    _printf(ALL_COMMANDS);

    _printf(HELP_BVB);
    _printf(HELP_HELP);
    _printf(HELP_LEADERBOARD);
    _printf(HELP_LOAD_PVB);
    _printf(HELP_LOAD_PVP);
    _printf(HELP_PVB);
    _printf(HELP_PVP);
    _printf(HELP_QUIT);

    _printf("\n");
}

void leaderboard()
{
    rating ratings[MAX_NB_RATINGS];
    int nb_ratings = load_all_ratings(ratings);
    sort_all_ratings(ratings, nb_ratings);

    clear_screen();
    print_leaderboard(ratings, nb_ratings);
    _printf(RETURN_MAIN_MENU);
    getchar();
}

void menu_start_pvb(){
    _printf(DIFFICULTY_INPUT_PROMPT);
    bot_difficulty_e bot_diff = input_bot_difficulty();
    if (bot_diff == -1){
        _printf(DIFFICULTY_INPUT_ERROR);
        getchar();
        return;
    }
    pvb_start(bot_diff);
}

void menu_load_pvb(){
    _printf(DIFFICULTY_INPUT_PROMPT);
    bot_difficulty_e bot_diff = input_bot_difficulty();
    if (bot_diff == -1){
        _printf(DIFFICULTY_INPUT_ERROR);
        getchar();
        return;
    }
    pvb_load(bot_diff);
}

void menu_start_bvb(){
    _printf(FIRST_DIFFICULTY_INPUT_PROMPT);
    bot_difficulty_e bot_diff = input_bot_difficulty();
    if (bot_diff == -1){
        _printf(DIFFICULTY_INPUT_ERROR);
        getchar();
        return;
    }
    _printf(SECOND_DIFFICULTY_INPUT_PROMPT);
    bot_difficulty_e bot_diff2 = input_bot_difficulty();
    if (bot_diff2 == -1){
        _printf(DIFFICULTY_INPUT_ERROR);
        getchar();
        return;
    }
    bvb_start(bot_diff, bot_diff2);
}