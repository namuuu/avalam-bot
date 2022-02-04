#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#ifdef __DEBUG__
	#define debug afficherPosition(p);

#else
	#define debug
	
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

// Menu that is displayed before the beginning of a game.
int startMenu();

/// Sets every bonus at the right place for every team.
// The usage of this fonction is used 4 times in the setup of the game, and should respect the following pattern :
//       Yellow Bonus, Red Bonus, Red Malus, Yellow malus
//
// T_Position : Board of the game
// Bonus : Which bonus is modified (ex: p.evolution.bonusJ)
// Team : Which team is considered, either Yellow (1) or Red (2)
int setBonus(T_Position p, octet bonus, int team);

/// Writes every game information in the ../web/data directory on a JS file.
void writeJS(T_Position p,  T_Score score);