#include <stdio.h>

#include "board.h"
#include "menu.h"
#include "input.h"
#include "display.h"
#include "gameloop.h"

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

    printf("- help : displays this text\n");
    printf("- leaderboard : displays a leaderboard stored in rating.dat\n");
    printf("- load-pvp : loads a 2 players game previously saved\n");
    printf("- pvp : start a 2 players game\n");
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