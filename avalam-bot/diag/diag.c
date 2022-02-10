#include <diag.h>

char *str_replace(char *orig, char *rep, char *with);

int main(int argc , char * argv[]) {

    if(argc == 1) {
        printf(RED "Mauvais arguments ! \n "RESET"Arguments : <diag> <fen>\n");
        return 1;
    }

    printf("Diagramme: "YEL"%s\n"RESET, argv[1]);
	printf("Fen: "YEL"%s"RESET"\n", argv[2]);

    FILE * fp, * fp2;
	int i,trait;
	char ch;

    writeJS(argv[1], argv[2]);
}

int writeJS(char diag[], char fen[]) {
    FILE * fp;

    char save[500];
    strcpy(save, path);
    strcat(save, filename);
    strcat(save, ".js");

    fp = fopen(save, "w+");

    fputs("traiterJson({\n", fp);

    fputs(STR_TURN":", fp);
	fprintf(fp, "%d,\n", ((strcmp(&fen[strlen(fen)-1],"r") == 0) ? 2 : 1));

    //put number of diag in the js doc

	fputs(STR_NUMDIAG":", fp);
	fprintf(fp, "%s,\n", diag);



	//put comment of diag in the js doc

	fputs(STR_NOTES":\"", fp);

    formatJS(fp);
	
	fputs("\",\n", fp);


	//put FEN of diag in the js doc
	fputs(STR_FEN":\"", fp);
	fprintf(fp, "%s\",\n", fen);

    fclose(fp);
}

int formatJS(FILE * fp) {
    printf("Description (vous pouvez saisir du HTML, Ctrl+D pour terminer) ? []"YEL"\n");
    system("cat > desc");

    FILE * fp2;
	//copy
	// ouvrir le fichier en lecture
	fp2 = fopen("desc", "r");

	// Lire le contenu du fichier

    char notes[500];
    while (fgets(notes, 500, fp2) != NULL) {
        strcpy(notes, str_replace(notes, "\n", "<br>"));
        fputs(notes, fp);
    }

	fclose(fp2);

    system("rm desc");
	//paste

    return 0;
}

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}