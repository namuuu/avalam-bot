/**************************************************************************/
/*Fichier: diag.c							   	*/
/*NOM :Robert Arthur Merabet Nawel Husson Augustin David Leevan				 						*/
/*GROUPE: E7  */
/* Version : 1.0									*/
/*Date : 09/02/2022							   		*/
/***************************************************************************/
#include <diag.h>
/***************************************************************************/
/* NOM FONCTION : fonction principale					           */
/* DESCRIPTION : Dans cette fonction, l'utilisateur saisi des arguments dans le terminale et cette fonction a pour but de récupérer les arguments pour les utiliser et les transformer */
/* Retourne :  0       			   */
/* Effets de bords : Saisie au clavier                                     */
/* Parametres en entree :int argc, char * argv[]				   */
/* Parametres en sortie :  entier                                                */
/***************************************************************************/



int main(int argc, char * argv[]){
    T_Position p;

	char chemin[UNKNOWN]="diag.js";

	// Stops the program if not enough arguments
	if(argc<=3){
		printf(RED "Mauvais arguments ! \n "RESET"Arguments : <diag> <fen>\n");
        return 1;
	}

	printf("Diagramme %s\n", argv[1]);
	printf("Fen : %s\n", argv[2]);


	//changement de nom
	printf("Fichier (sera créé dans le répertoire ./web/data s'il existe) ? [diag.js]\n");
	
	fgets(chemin, UNKNOWN, stdin);

	if (strcasecmp(chemin,"\n") != 0) {
		chemin[strlen(chemin)-1] = '\0';
		strcpy(filename, chemin);
	}

	printf("Description (vous pouvez saisir du HTML, Ctrl+D pour terminer) ? []"YEL"\n");
	char notes[500];
	readNotes(notes);

	readFEN(&p,argv[2], argv[3]);

    writeJS(p, evaluerScore(p), notes, argv[1]);//écrit le FEN dans le fichier JS
	//printf("dernier getchar\n");
	getchar();
}
/***************************************************************************/
/* NOM FONCTION : readFEN					           */
/* DESCRIPTION : Il transforme le deuxième argument en placement dans le plateau       */
/* Retourne : 0     			   */
/* Parametres en entree :T_Position *p, char argv[], char trait[]						   */
/* Parametres en sortie : entier                                                */
/***************************************************************************/


int readFEN(T_Position *p, char argv[], char trait[]) {
    int i=0,j=0,k=0;
    for(i=0;i<48;i++){
        p->cols[i].nb=0;
        p->cols[i].couleur=0;
    }
    //intialision des bonus et des malus à -1
    p->evolution.bonusJ=-1;
    p->evolution.bonusR=-1;
    p->evolution.malusJ=-1;
    p->evolution.malusR=-1;
    i=0;
    if(argv!=NULL){
		while(argv[j]!='\0') {
			switch(argv[j]) { //Switch pour les différentes possibilitées
				case 'u' : 
				p->cols[i].nb=1;//la taille de la pile
				p->cols[i].couleur=1;//la couleur
				i++;
				break;
				case 'd':
				p->cols[i].nb=2;
				p->cols[i].couleur=1;
				i++;
				break;
				case 't':
				p->cols[i].nb=3;
				p->cols[i].couleur=1;
				i++;
				break;
				case 'q':
				p->cols[i].nb=4;
				p->cols[i].couleur=1;
				i++;
				break;
				case 'c': 
				p->cols[i].nb=5;
				p->cols[i].couleur=1;
				i++;
				break;
				case 'U': 
				p->cols[i].nb=1;
				p->cols[i].couleur=2;
				i++;
				break;
				case 'D':
				p->cols[i].nb=2;
				p->cols[i].couleur=2;
				i++;
				break;
				case 'T': 
				p->cols[i].nb=3;
				p->cols[i].couleur=2;
				i++;
				break;
				case 'Q':
				p->cols[i].nb=4;
				p->cols[i].couleur=2;
				i++; 
				break;
				case 'C':
				p->cols[i].nb=5;
				p->cols[i].couleur=2;
				i++;
				break;
				case 'b':
				if(p->evolution.bonusJ==255){
					i=i+1;
					p->evolution.bonusJ=i;
				}
				break;
				case 'B':
				if(p->evolution.bonusR==255){
					i=i+1;
					p->evolution.bonusR=i;
				}
				break;
				case 'm':
				if(p->evolution.malusJ==255){
					i=i+1;
					p->evolution.malusJ=i;
				}
				break;
				case 'M':
				if(p->evolution.malusR==255){
					i=i+1;
					p->evolution.malusR=i;
				}
				break;
				case '0'...'9':
				if(argv[j+1]>'0'&& argv[j+1]<'9' ){

						int r= (argv[j] - '0')*10  + (argv[j+1] - '0');
						for(int k=0;k<=r;k++){
							p->cols[i+k].couleur = 0;
							p->cols[i+k].nb = 0;
						}
						j=j+1;
						
						while(argv[j+1]>'0'&& argv[j+1]<'9')
						{
							j=j+1;
						}
						i=i+r+1;
				}else{

					int r= (argv[j] - '0');
					for(int k=0; k<=r; k++) {
						p->cols[i+k].couleur = 0;
						p->cols[i+k].nb = 0;
					}
					i=i+r+1;
				}
				break;
			}
		j=j+1;
    	}

		if(trait[0]=='r') {//initialisation du trait
			p->trait=2;
		} else {
			p->trait=1;
		}
		return 0;
	}
}

//	fonction de création de json
/***************************************************************************/
/* NOM FONCTION : writeJS					           */
/* DESCRIPTION : A l'aide de fputs et fprintf et des variables, on écrit dans le JS.      */
/* Retourne :rien    			   */
/* Parametres en entree :T_Position p, T_Score score, char notes[], char diag[]						   */
/* Parametres en sortie : fichier.js avec le contenue                                               */
/***************************************************************************/
void writeJS(T_Position p, T_Score score, char notes[], char diag[]) {

	FILE * fp;

    char save[500];
    strcpy(save, path);
    strcat(save, filename);
    strcat(save, ".js");

    fp = fopen(save, "w+");

	fputs("traiterJson({\n", fp);

	
	
	fputs(STR_TURN":", fp);
	fprintf(fp, "%d,\n", p.trait);
	

    fputs(STR_NUMDIAG":", fp);
	fprintf(fp, "%s,\n", diag);


    fputs(STR_NOTES":\"", fp);
	fprintf(fp, "%s", notes);
	fputs("\",\n", fp);

	fputs(STR_SCORE_J":", fp);
	fprintf(fp, "%d,\n", score.nbJ);
	
	fputs(STR_SCORE_J5":", fp);
	fprintf(fp, "%d,\n", score.nbJ5);
	
	fputs(STR_SCORE_R":", fp);
	fprintf(fp, "%d,\n", score.nbR);
	
	fputs(STR_SCORE_R5":", fp);
	fprintf(fp, "%d,\n", score.nbR5);
	
	fputs(STR_BONUS_J":", fp);
	fprintf(fp, "%d,\n", p.evolution.bonusJ);
	
	fputs(STR_MALUS_J":", fp);
	fprintf(fp, "%d,\n", p.evolution.malusJ);
	
	fputs(STR_BONUS_R":", fp);
	fprintf(fp, "%d,\n", p.evolution.bonusR);
	
	fputs(STR_MALUS_R":", fp);
	fprintf(fp, "%d,\n", p.evolution.malusR);
	
	fputs(STR_COLS":[\n", fp);

	
	for(int i = 0; i < NBCASES-1; i++)
	{
		fprintf(fp, "\t{"STR_NB":%d, "STR_COULEUR":%d},\n", p.cols[i].nb,p.cols[i].couleur);
	}
	fprintf(fp, "\t{"STR_NB":%d, "STR_COULEUR":%d}\n]\n});", p.cols[NBCASES-1].nb,p.cols[NBCASES-1].couleur);
	
	
	fclose(fp); 

}
/***************************************************************************/
/* NOM FONCTION : readNotes				           */
/* DESCRIPTION : Cette fonction ouvre un fichier pour écrire le texte donner par l'utilisateur                                              */
/* Retourne :0         			   */
/* Parametres en entree :char notes[]						   */
/* Parametres en sortie :entier                                         */
/***************************************************************************/
int readNotes(char notes[]) {
    
    system("cat > desc");

    FILE * fp2;
	//copy
	// ouvrir le fichier en lecture
	fp2 = fopen("desc", "r");

	// Lire le contenu du fichier
    while (fgets(notes, 500, fp2) != NULL) {
        strcpy(notes, str_replace(notes, "\n", "<br>"));
    }

	fclose(fp2);

    system("rm desc");
	//paste

    return 0;
}

// You must free the result if result is non-NULL.
/***************************************************************************/
/* NOM FONCTION : str_replace				           */
/* DESCRIPTION :                                             */
/* Retourne :entier : result         			   */
/* Parametres en entree :char *orig, char *rep, char *with						   */
/* Parametres en sortie :char *                                           */
/***************************************************************************/
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