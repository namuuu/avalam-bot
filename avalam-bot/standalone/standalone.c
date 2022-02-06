#include <standalone.h>

int main(int argc, char * argv[]) {

	char path[500] = "";
	setPath(path, argc, argv);

	T_Position p;
	T_ListeCoups l;
	int ori, dest;

	p = getPositionInitiale();

	writeJS(p, evaluerScore(p));

	// Displays the startMenu, and stops the program if the user decided to.
	int i = startMenu();
	if(i == 1) {
		return 0;
	}
	
	

	//	initialisation des bonus malus
	
	// Pour pouvoir se permettre d'update le JSON à chaque Bonus / Malus, il est obligatoire de les déplacer en dehors du plateau.
	// Autrement, il y seraient affichés par défaut en case 0, ce qui n'est pas souhaité.
	p.evolution.bonusJ =-1;
	p.evolution.bonusR =-1;
	p.evolution.malusR =-1;
	p.evolution.malusJ =-1;
		
	printf(WHT"Sélection du "YEL"Bonus Jaune"RESET"\n");
	setBonus(p, &p.evolution.bonusJ, JAU, -1);
	
	printf(WHT"Sélection du "RED"Bonus Rouge"RESET"\n");
	setBonus(p, &p.evolution.bonusR, ROU, -1);
	
	printf(WHT"Sélection du "RED"Malus Rouge"RESET"\n");
	setBonus(p, &p.evolution.malusR, ROU, p.evolution.bonusR);
	
	printf(WHT"Sélection du "YEL"Malus Jaune"RESET"\n");
	setBonus(p, &p.evolution.malusJ, JAU, p.evolution.bonusJ);

	writeJS(p, evaluerScore(p));


	//	Boucle de jeu
	while(getCoupsLegaux(p).nb!=0) {
		
		printf("qui joue: %s", COLNAME(p.trait));
		
		printf("\n origine:");
		scanf("%d",&ori);
		
		printf("\n destination:");
		scanf("%d",&dest);
		
		p = jouerCoup(p, ori, dest);
		
		affpos;
		
		writeJS(p, evaluerScore(p));
		
	}

	displayScore(p);
	
	
return 0;
}


// Menu that is displayed before the beginning of a game.
int startMenu() {
	system("clear");

	int choice = 0;

	while(choice != 1) {
		printf("\n\t\tAVALAM - créé par L.A.N.A\n");
		printf("\n Sélectionne une "YEL"option !\n"RESET);
		printf("\n\t" YEL "1" RESET " - Lance la partie !");
		printf("\n\t" YEL "2" RESET " - Ouvre la partie graphique du jeu dans ton navigateur !");

		printf("\n\t" YEL "9" RESET " - Quitter le jeu\n");
		printf("\nOption choisie: "CYN);

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf(GRN"\nLa partie a été lancée, bonne chance !\n"RESET);
			break;
		case 2:
			printf(MAG"\n\tOuverture de ton navigateur..\n");
			system("xdg-open file:///home/pi/Documents/Projet%20MDJ/avalam-bot/web/avalam-refresh.html");
			break;
		case 9:
			printf(MAG"Arrêt du programme...\n\n" GRN "Merci d'avoir joué !\n\n" RESET);
			return 1;
			break;
		default:
			printf(RED"\n\t Votre choix n'a pas été reconnu, essayez-en un autre !\n"RESET);
			break;
		}
	}

	system("clear");

	return 0;
}

void setPath(char path[], int argc, char * argv[]) {

	//choix du chemin d'enregistrement
	if(argc>1){
		
		//if(argv[])
		int i;

		for(i=1; i<argc-1;i++){ 
			strcat(path,argv[i]); strcat(path,"/"); 
		}
		strcat(path,argv[i]);
	}
	else strcat(path, "../web/data/refresh-data.js");
	cheminjs;
}


// Writes every game information in the ../web/data directory on a JS file.
void writeJS(T_Position p, T_Score score) {
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

/// Sets every bonus at the right place for every team.
int setBonus(T_Position p, octet *bonus, int team, int locked) {
	int selecteur;

	writeJS(p, evaluerScore(p));

	do {
		printf("Position du bonus: ");
		scanf("%d",&selecteur);
		*bonus = selecteur;
	} while(p.cols[selecteur].couleur != team || selecteur == locked);

	printf(GRN"Le choix a bien été pris en compte!\n\n"RESET);

	return selecteur;
}

void displayScore(T_Position p) {

	//afficher qui  a gagner + les point
	if(evaluerScore(p).nbJ==evaluerScore(p).nbR)//si egalité
	{
		if(evaluerScore(p).nbJ5<evaluerScore(p).nbR5) {
			printf("\nRouge gagnant\n");
			return; 
		} else {
			printf("\njaune gagnant\n"); 
			return;
		}
	}

	if(evaluerScore(p).nbJ<evaluerScore(p).nbR) {
		printf("\nRouge gagnant\n"); 
		return;
	} else { 
		printf("\njaune gagnant\n");
		return;
	}

}
