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
    T_Position p;

	char chemin[UNKNOWN]="diag.js";
	char tmp[UNKNOWN]="../web/data/";


	if(argc==1){
		printf("diag <numDiag> <fen>\n");
		return 0;
	}

	T_Score score;
    score.nbJ5=1;
    score.nbR5=0;   
    score.nbR=0;
    score.nbJ=0;
    char description[500]="Bonjour";
    printf("p.cols[1].nb=%d\n",p.cols[1].nb);
    p.cols[1].nb=5;
    printf("p.cols[1].nb=%d\n",p.cols[1].nb);


    printf("p.cols[1].nb=%d\n",p.cols[1].nb);
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
	
	FEN(p,argv[2]);
    //void writeJSON(T_Position p, T_Score score, char *chemin ,char *argv[], char description[])
    writeJSON( p,  score, chemin ,argv, description);
	//printf("u=%d",p.cols[0].nb);





	/*FILE * fp;

	fp = fopen(chemin, "w+");
	fputs("coucou", fp);



	
	if(strcmp(&argv[2][strlen(argv[2])-1],"r") == 0) trait = 2;else trait = 1;
	


	fclose(fp); */

}
int FEN(T_Position p, char argv[]){
    int i=0,j=0,k=0;
  // printf("a=%c",argv[0]);
 char ch;
    
    for(i=0;i<48;i++){
        p.cols[i].nb=0;
        p.cols[i].couleur=0;
    }
    
    p.evolution.bonusJ=-1;
    p.evolution.bonusR=-1;
    p.evolution.malusJ=-1;
    p.evolution.malusR=-1;
    i=0;

 //j=0;
    
    while(argv[j]!=NULL){
        
       //j=j+1;
    switch(argv[j])
    {
        
        case 'u' : 
        p.cols[i].nb=1;
        p.cols[i].couleur=1;
        i=i+1;
        break;
        case 'd':
       
        p.cols[i].nb=2;
        p.cols[i].couleur=1;
        i++;
        break;
        case 't':
        p.cols[i].nb=3;
        p.cols[i].couleur=1;
        i++;
        break;
        case 'q':
        p.cols[i].nb=4;
        p.cols[i].couleur=1;
        i++;
        break;
        case 'c': 
        p.cols[i].nb=5;
        p.cols[i].couleur=1;
        i++;
        break;
        case 'U': 
        p.cols[i].nb=1;
        p.cols[i].couleur=2;
        i++;
        break;
        case 'D':
        p.cols[i].nb=2;
        p.cols[i].couleur=2;
        i++;
        break;
        case 'T': 
        printf("Tj=%d\n",j);
        p.cols[i].nb=3;
        p.cols[i].couleur=2;
        i++;
        break;
        case 'Q':
        p.cols[i].nb=4;
        p.cols[i].couleur=2;
        i++; 
        break;
        case 'C':
        p.cols[i].nb=5;
        p.cols[i].couleur=2;
        i++;
        break;
        case 'b':
        if(p.evolution.bonusJ==-1){
            p.evolution.bonusJ=i+1;
        }
        break;
        case 'B':
        printf("Bj=%d\n",j);
        if(p.evolution.bonusR==-1){
            p.evolution.bonusR=i+1;
        }
        break;
        case 'm':
        printf("mj=%d\n",j);
        if(p.evolution.malusJ==-1){
            p.evolution.malusJ=i+1;
        }
        break;
        case 'M':
        if(p.evolution.malusR==-1){
            p.evolution.malusR=i+1;
        }
        case '0...9':
            strcat(ch,argv[j]);
        if(argv[j+1=='0...9']){
            strcat(ch,argv[j+1]);
        }
        j=ch;
        break;
    }
  j=j+1;
    }
 
 if(argv[j+1]=='r'){
     p.trait=2;
 }else{
     p.trait=1;
 }

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