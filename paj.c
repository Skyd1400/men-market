/*
 * FICHIER : paj.c
 * DATE CREATION : 10/5/2017
 * DESCRIPTION : Se pati sa ki jere konsep paj yo
 *
 */
#include <stdio.h>
#include "paj.h"

char *bordure = "=====================================================================\n";
char *bordure_fine = "---------------------------------------------------------------------\n";

char *app_name = "       __   __ _____ _   _      __   __  ___  _   _______ _____\n      |  \\ /  |  ___) \\ | |    |  \\ /  |/ _ \\| | / /  ___|_   _)\n      |   v   | |_  |  \\| |    |   v   | |_| | |/ /| |_    | |\n      | |\\_/| |  _) |     | == | |\\_/| |  _  |   < |  _)   | |\n      | |   | | |___| |\\  |    | |   | | | | | |\\ \\| |___  | |\n      |_|   |_|_____)_| \\_|    |_|   |_|_| |_|_| \\_\\_____) |_|\n";

void afiche_antet(char *titre)
{
    ScreenClear();
    char text[100];
    textcolor(LIGHTRED);
    cputs(bordure);
    cputs(app_name);
    cputs("\n");
    cputs(bordure);

    gotoxy(26, 11);
    textcolor(YELLOW);
    sprintf(text, ":: %s ::", titre);
    cputs(text);
    gotoxy(1, 13);
    textcolor(RED);
    cputs(bordure_fine);
}
