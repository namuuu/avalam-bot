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

void writeJSON(T_Position p,  T_Score score, char *chemin,char *argv[], char descrition[]);



int main(int argc, char * argv[]){


	if(argc==1){
		printf("diag <numDiag> <fen>\n");
		return 0;
	}

	
	
	printf("Diagramme %s\n", argv[1]);
	printf("Fen : %s\n", argv[2]);


	FILE * fp, * fp2;
	int i,trait;
	char ch;




	fp = fopen("FEN", "w+");
	fputs("traiterJson({\n", fp);



	//mettre le trait dans le js
	if(strcmp(&argv[2][strlen(argv[2])-1],"r") == 0) trait = 2;else trait = 1;

	fputs(STR_TURN":", fp);
	fprintf(fp, "%d,\n", trait);


	//put number of diag in the js doc

	fputs(STR_NUMDIAG":", fp);
	fprintf(fp, "%s,\n", argv[1]);



	//put comment of diag in the js doc

	printf("Description (vous pouvez saisir du HTML, Ctrl+D pour terminer) ? []");


	fputs(STR_NOTES":\"", fp);
	system("cat > desc");

	//copy
	 	// ouvrir le fichier en lecture
		fp2 = fopen("desc", "r");

	
		// Lire le contenu du fichier
		while((ch = getc(fp2)) != EOF) putc(ch, fp);

		
		fclose(fp2);
		system("rm desc");
	//paste
	fputs("\",\n", fp);


	//put FEN of diag in the js doc
	fputs(STR_FEN":\"", fp);
	fprintf(fp, "%s\",\n", argv[2]);








	fclose(fp);


	/*
	//description
	FILE * fichier;
	char description[UNKNOWN]="";


	printf("Description (vous pouvez saisir du HTML, Ctrl+D pour terminer) ?\n");
	system("cat > desc");

	fichier = fopen("desc", "r");
	
	



	printf("\nmaintenant\n");


	fclose(fichier);
	
	printf("la\n");




*/

	

	
	

	
	

	//writeJSON(p, evaluerScore(p),chemin, argv, description);
	

	

	
	
	

}


//	fonction de création de json
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

}
