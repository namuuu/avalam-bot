/**************************************************************************/
/*Fichier: lanalib.c							   	*/
/*NOM :Robert Arthur Merabet Nawel Husson Augustin David Leevan				 						*/
/*GROUPE: E7  */
/* Version : 1.0									*/
/*Date : 09/02/2022							   		*/
/***************************************************************************/

#include <lanalib.h>
/***************************************************************************/
/* NOM FONCTION : fonction principale					           */
/* DESCRIPTION : Dans cette fonction, Il demande les positions des bonus et des malus en les positionnant dans un premier temps dans la position -1.Puis il propose un menu pour demander se que l'utilisateur veut faire.
Dans la première case,il propose de jouer en demandant le deplacement du pion.Dans le deuxième case, il demande d'afficher la position. Et dans le troisième case, il ouvre dans le navigateur. Dans le dernier case, il arrête le programme. */
/* Retourne :  0       			   */
/* Effets de bords : Saisie au clavier                                     */
/* Parametres en entree :Ttabpers Rep, int der 						   */
/* Parametres en sortie :  entier                                                */
/***************************************************************************/

int main(int argc, char * argv[]) {

	// Changes the path_standalone if main() has arguments
	setPath(path_standalone, argc, argv);

	T_Position p;
	int ori, dest;

	// Sets the board to default values based on what's in "topologie.h".
	p = getPositionInitiale();

	writeJS(p, evaluerScore(p));

	// Displays the startMenu, and stops the program if the user decided to.
	int i = startMenu();
	if(i == 1) {
		return 0;
	}
	
	

	/// Initialissation des bonus et malus
	
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

	system("clear");


	//	Boucle de jeu
	while(getCoupsLegaux(p).nb!=0) {


		printf(RESET"\n\t\tAu tour de: %s\n", STR_TEAM_NAME(p.trait));
		printf("\nOption choisie: %s", STR_TEAM_COL(p.trait));

		
		printf("\nVous jouez un coup!\n\n Origine: %s"RESET, STR_TEAM_COL(p.trait));
		scanf("%d",&ori);
		
		printf("\n Destination: %s"RESET, STR_TEAM_COL(p.trait));
		scanf("%d",&dest);

		p = jouerCoup(p, ori, dest);

		system("clear");

		affpos;


		
		writeJS(p, evaluerScore(p));
		
	}

	displayScore(p);
	
	
return 0;
}
/***************************************************************************/
/* NOM FONCTION : startMenu					           */
/* DESCRIPTION : Il propose un menu dans lequel il propose 3 choix (1-lancer la partie et 2-Ouvre la partie graphique du jeu dans ton navigateur ! et 9-Quitter le jeu)      */
/* Retourne : 0     			   */
/* Parametres en entree :char path[]						   */
/* Parametres en sortie :                                                 */
/***************************************************************************/


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
		printf1(DEBUG"\n DEBUG > Current save path_standalone: %s\n"RESET, path_standalone);
		printf("\nOption choisie: "CYN);

		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf(GRN"\nLa partie a été lancée, bonne chance !\n"RESET);
			break;
		case 2:
			printf(MAG"\n\tOuverture de ton navigateur..\n");
			system("xdg-open ../web/avalam-refresh.html");
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
/***************************************************************************/
/* NOM FONCTION : gameMenu					           */
/* DESCRIPTION :La fonction affiche le menu du jeu.Il propose 4 choix
1- Jouer un coup et 2- Afficher toutes les positions et 3- Ouvre la partie graphique du jeu dans ton navigateur 4-    */
/* Retourne :  choice       			   */
/* Parametres en entree : T_Position p						   */
/* Parametres en sortie : choice->entier                                                  */
/***************************************************************************/

/*int gameMenu(T_Position p) {
	int choice = 0;

	printf(RESET"\n\t\tAu tour de: %s\n", STR_TEAM_NAME(p.trait));

	printf("\n Sélectionne une "CYN"option !\n"RESET);
	printf("\n\t" CYN "1" RESET " - Jouer un coup\n");

	printf("\n\t" CYN "6" RESET " - Afficher toutes les positions");
	printf("\n\t" CYN "7" RESET " - Ouvre la partie graphique du jeu dans ton navigateur !\n");

	printf("\n\t" CYN "9" RESET " - Quitter le jeu\n");
	
	printf("\nOption choisie: %s", STR_TEAM_COL(p.trait));

	scanf("%d", &choice);
	printf(RESET);

	return 1;
}*/

/***************************************************************************/
/* NOM FONCTION : setPath					           */
/* DESCRIPTION :La fonction a pour principe de mettre a jour le chemin d'enregistrement
	elle concane les arguments dans le cas ou il y a présence d'espace*/
/* Retourne :Rien         			   */
/* Parametres en entree :char path[], int argc, char * argv[]					   */
/* Parametres en sortie :Aucun                                                 */
/***************************************************************************/



void setPath(char path_standalone[], int argc, char * argv[]) {

	if(argc>1){
		strcpy(path_standalone,"");
		
		int i;
		printf("%d\n",argc);
		for(i=1; i<argc-1;i++){
			strcat(path_standalone,argv[i]); strcat(path_standalone," "); 
		}
		
		strcat(path_standalone,argv[i]);

	}

}


/***************************************************************************/
/* NOM FONCTION : writeJS					           */
/* DESCRIPTION : A l'aide de fputs et fprintf et des variables, on écrit dans le JS.      */
/* Retourne :rien    			   */
/* Parametres en entree :T_Position p, T_Score score						   */
/* Parametres en sortie : fichier.js avec le contenue                                               */
/***************************************************************************/

// Writes every game information in the ../web/data directory on a JS file.
void writeJS(T_Position p, T_Score score) {
	printf1(DEBUG"\nDEBUG > Save data on %s\n"RESET, path_standalone);

	FILE * fp;
	fp = fopen(path_standalone, "w+");
	
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

/***************************************************************************/
/* NOM FONCTION : setBonus				           */
/* DESCRIPTION :la fonction demande la position des bonus et malus et produit une boucle infini tant que la position donné                                             */
/* Retourne :entier : selecteur         			   */
/* Parametres en entree :T_Position p, octet *bonus, int team, int locked						   */
/* Parametres en sortie :                                                 */
/***************************************************************************/

/// Sets every bonus at the right place for every team.
int setBonus(T_Position p, octet *bonus, int team, int locked) {
	int selecteur;

	// The flag checks if the bonus position is valid, if it's still at 1 at the end of a do while, then it is.
	int flag;

	writeJS(p, evaluerScore(p));

	// The reason of why the flag is checked for the second and third check, is that with offset bonuses we still can trigger
	// those errors, and if it's preferable to not trigger errors for no reason in order to be more user-friendly
	do {
		flag = 1;

		printf("\nPosition du bonus: ");
		scanf("%d",&selecteur);
		*bonus = selecteur;
		if (selecteur < 0 || selecteur >= NBCASES) {
			printf("%sCette position ne se situe pas sur le plateau! (Plateau: 0 à 47)\n"RESET, STR_TEAM_COL(team));
			flag = 0;
		}
		if (flag == 1 && selecteur == locked) {
			printf("%sCette position est déjà occupée par votre bonus!\n"RESET, STR_TEAM_COL(team));
			flag = 0;
		}
		if(flag == 1 && p.cols[selecteur].couleur != team) {
			printf("%sCette position n'est pas de votre couleur!\n"RESET, STR_TEAM_COL(team));
			flag = 0;
		}
		
	} while(flag == 0);

	printf(GRN"Le choix a bien été pris en compte!\n\n"RESET);

	return selecteur;
}



/***************************************************************************/
/* NOM FONCTION : displayScore					           */
/* DESCRIPTION : Il compare les scores est si il y a égalité.Il va réutilisé une boucle if pour comparer les piles de 5.      */
/* Retourne :affiche le gagnant      			   */
/* Parametres en entree :T_Position p					   */
/* Parametres en sortie :pas de sortie                                                */
/***************************************************************************/
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
