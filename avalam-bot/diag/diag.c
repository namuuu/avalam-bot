#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>
#include <string.h>

#ifdef __DEBUG__
	#define affpos afficherPosition(p)
	#define cheminjs puts(chemin)
#else
	#define affpos
	#define cheminjs
#endif

//void writeJSON(T_Position p,  T_Score score, char *chemin,char *argv[], char descrition[]);



int main(int argc, char * argv[]){

	char chemin[UNKNOWN]="diag.js";
	char tmp[UNKNOWN]="../web/data/";


	if(argc==1){
		printf("diag <numDiag> <fen>\n");
		return 0;
	}

	
	
	printf("Diagramme %s\n", argv[1]);
	printf("Fen : %s\n", argv[2]);


	//changement de nom
	printf("Fichier (sera créé dans le répertoire ./web/data s'il existe) ? [diag.js]");
	
	fgets(chemin, UNKNOWN, stdin);

	if (strcasecmp(chemin,"\n") == 0)
	{
		strcpy(chemin,"../web/data/diag.js");
		puts(chemin);
	}
	else
	{
		chemin[strlen(chemin)-1] = '\0';
		strcat(tmp,chemin);
		strcpy(chemin,tmp);
	}
	

	





	FILE * fp;

	fp = fopen(chemin, "w+");
	fputs("coucou", fp);



	/*
	if(strcmp(&argv[2][strlen(argv[2])-1],"r") == 0) trait = 2;else trait = 1;
	*/


	fclose(fp);

}


/*	fonction de création de json
void writeJSON(T_Position p, T_Score score, char *chemin ,char *argv[], char description[]) {



	
	FILE * fp;
	
	fp = fopen(chemin, "w+");
	fputs("traiterJson({\n", fp);

	
	
	fputs(STR_TURN":", fp);
	fprintf(fp, "%d,\n", p.trait);
	

    fputs(STR_NUMDIAG":", fp);
	fprintf(fp, "%s,\n", argv[1]);


    fputs(STR_NOTES":", fp);
	fprintf(fp, "\"%s\",\n", description);





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

}*/
