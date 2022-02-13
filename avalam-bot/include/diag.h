#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>
#include <string.h>

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

char path[500] = "../web/data/";
char filename[500] = "fic";

void writeJS(T_Position p, T_Score score, char notes[], char diag[]);
int readNotes(char notes[]);
int readFEN(T_Position *p, char argv[], char trait[]);

char *str_replace(char *orig, char *rep, char *with);