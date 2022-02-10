#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>
#include <string.h>

#ifdef __DEBUG__
	#define affpos afficherPosition(p)
	#define cheminjs puts(path)
#else
	#define affpos
	#define cheminjs
#endif

// Basic colors displayed in the command interface
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define DEBUG "\x1B[95m"

#define STR_TEAM_NAME(team) ((team == ROU) ? RED"Rouge"RESET : YEL"Jaune"RESET)
#define STR_TEAM_COL(team) ((team == ROU) ? RED : YEL)

// Path of the current save file.
char path_standalone[500] = "../web/data/refresh-data.js";
char path_diag[500] = "../web/data/";
char diag_file[500] = "fic.js";

// Menu that is displayed before the beginning of a game.
int startMenu();

int gameMenu(T_Position p);

/// Sets every bonus at the right place for every team.
// The usage of this fonction is used 4 times in the setup of the game, and should respect the following pattern :
//       Yellow Bonus, Red Bonus, Red Malus, Yellow malus
//
// T_Position : Board of the game
// Bonus : Which bonus is modified (ex: p.evolution.bonusJ)
// Locked : Prevents the player to put the malus on the case already taken by the bonus ; -1 is used when every position is safe.
int setBonus(T_Position p, octet *bonus, int team, int locked);

/// Writes every game information in the selected path on a JS file.
void writeJS(T_Position p,  T_Score score);

/// Displays the current score of the game.
void displayScore(T_Position p);

/// Changes the path of the save file to a custom one.
// path : Path of the current save file.
// argc : Lenght of the new path
// argv : The new path
void setPath(char path[], int argc, char * argv[]);

//
void setCustomPath(char path[], char new[]);