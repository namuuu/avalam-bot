#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

#ifdef __DEBUG__
	#define debug afficherPosition(p);

#else
	#define debug
	
#endif

void writeJSON(T_Position p,  T_Score score);



int main(){
	
	FILE* fictest = NULL;
	FILE* fictest2 = NULL;

	
	
	T_Position p; 
	T_ListeCoups l; 
	int ori,dest;
	
	T_Evolution e;
	p = getPositionInitiale();
	
	int selecteur;
	
	writeJSON(p, evaluerScore(p));
	
	
	
	p.evolution.bonusJ =-1;
	p.evolution.bonusR =-1;
	p.evolution.malusR =-1;
	p.evolution.malusJ =-1;
	
	
//	initialisation des bonus malus
	do{
		
	printf("\n bonus Jaune:");
	scanf("%d",&selecteur);
	p.evolution.bonusJ = selecteur;
		
	}while(p.cols[selecteur].couleur != JAU);
	writeJSON(p, evaluerScore(p));
	
	do{
	printf("\n bonus Rouge:");
	scanf("%d",&selecteur);
	p.evolution.bonusR = selecteur;
	}while(p.cols[selecteur].couleur != ROU);
	writeJSON(p, evaluerScore(p));
	
	do{
	printf("\n malus Rouge:");
	scanf("%d",&selecteur);
	p.evolution.malusR = selecteur;
	}while(p.cols[selecteur].couleur != ROU);
	writeJSON(p, evaluerScore(p));
	
	do{
	printf("\n malus Jaune:");
	scanf("%d",&selecteur);
	p.evolution.malusJ = selecteur;
	}while(p.cols[selecteur].couleur != JAU);
		writeJSON(p, evaluerScore(p));
	
	
	
	debug


//	boucle de jeu
	while(getCoupsLegaux(p).nb!=0)
	{
		
		
		afficherScore(evaluerScore(p)); 
		
		
		printf("qui joue: %s", COLNAME(p.trait));
		
		printf("\n origine:");
		scanf("%d",&ori);
		
		printf("\n destination:");
		scanf("%d",&dest);
		
		p = jouerCoup(p, ori, dest);
		
		debug
		
		writeJSON(p, evaluerScore(p));

		
	}
	
return 0;
}


//	fonction de création de json
void writeJSON(T_Position p, T_Score score) {
	FILE * fp;
	fp = fopen("../web/data/refresh-data.js", "w+");
	
		fputs("traiterJson({\n", fp);
	
	
	fputs(STR_TURN":", fp);
	fprintf(fp, "%d,\n", p.trait);
	
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
