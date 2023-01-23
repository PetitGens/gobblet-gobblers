#include <stdio.h>

#include "../headers/board.h"
#include "../headers/menu.h"
#include "../headers/input.h"
#include "../headers/display.h"
#include "../headers/gameloop.h"
#include "../headers/bot.h"

void main_menu()
{
    bool running = true;
    bool display_intro = true;

    while(running)
    {
        if (display_intro)
        {
            clear_screen();

            printf("Gobblet Gobbers main menu :\n\n");

            printf("Enter 'pvp' to start a 2 players game.\n");
            printf("Enter 'help' for other commands.\n");
            printf("\n");

            display_intro = false;
        }

        printf(">");
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
                printf("exiting game program.\n");
                running = false;
                break;
            case LEADERBOARD:
                leaderboard();
                display_intro = true;
                break;
            default:
                printf("uknown command\n");
        }
    }
}

void main_help()
{
    printf("\nAll commands :\n\n");

    printf("- bvb : starts a game between 2 bots\n");
    printf("- help : displays this text\n");
    printf("- leaderboard : displays a leaderboard stored in rating.dat\n");
    printf("- load-pvb : loads a game against a bot previously saved\n");
    printf("- load-pvp : loads a 2 players game previously saved\n");
    printf("- pvb : starts a game against a bot\n");
    printf("- pvp : starts a 2 players game\n");
    printf("- quit : exits the game program\n");

    printf("\n");
}

void leaderboard()
{
    rating ratings[MAX_NB_RATINGS];
    int nb_ratings = load_all_ratings(ratings);
    sort_all_ratings(ratings, nb_ratings);

    clear_screen();
    print_leaderboard(ratings, nb_ratings);
    printf("Press return to get back to the main menu...");
    getchar();
}

void menu_start_pvb(){
    printf("Please choose bot difficulty (1 for easy, 2 for medium...) : ");
    bot_difficulty_e bot_diff = input_bot_difficulty();
    if (bot_diff == -1){
        printf("Invalid input, press return to get back to the main menu...");
        getchar();
        return;
    }
    pvb_start(bot_diff);
}

void menu_load_pvb(){
    printf("Please choose bot difficulty (1 for easy, 2 for medium...) : ");
    bot_difficulty_e bot_diff = input_bot_difficulty();
    if (bot_diff == -1){
        printf("Invalid input, press return to get back to the main menu...");
        getchar();
        return;
    }
    pvb_load(bot_diff);
}

void menu_start_bvb(){
    printf("Please choose the first bot's difficulty (1 for easy, 2 for medium...) : ");
    bot_difficulty_e bot_diff = input_bot_difficulty();
    if (bot_diff == -1){
        printf("Invalid input, press return to get back to the main menu...");
        getchar();
        return;
    }
    printf("Please choose the second bot's difficulty (1 for easy, 2 for medium...) : ");
    bot_difficulty_e bot_diff2 = input_bot_difficulty();
    if (bot_diff2 == -1){
        printf("Invalid input, press return to get back to the main menu...");
        getchar();
        return;
    }
    bvb_start(bot_diff, bot_diff2);
}