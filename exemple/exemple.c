#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>

int main(void) {
	T_Position p; 
	T_ListeCoups l; 

	printf0("Création de la position initiale ...\n"); 
	p = getPositionInitiale();
	
	printf0("Récupération des coups légaux de la position initiale ...\n"); 
 	l = getCoupsLegaux(p);

	printf("Ceci est un programme d'exemple pour le livrable 1\n");
	printf("Depuis la position initiale du jeu, il y a %d coups possibles\n", l.nb);

	printf("Depuis la position initiale du jeu, le trait est aux %ss\n", COLNAME(p.trait));


	return 0;
}
