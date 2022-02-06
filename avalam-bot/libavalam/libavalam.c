#include <stdio.h>
#include "avalam.h"

extern T_Voisins topologie[NBCASES]; 
T_Position positionInitiale; 


octet nbVoisins(octet numCase) {
	// renvoie le nombre de voisins d'une case
	return topologie[numCase].nb; 
}

T_Voisins getVoisins(octet numCase) {
	return topologie[numCase]; 
}

void listerVoisins(octet numCase) {
	int i; 
	T_Voisins v = getVoisins(numCase);
	for(i=0;i<v.nb;i++) {
		printf("%d ",v.cases[i]);
	}
	printf("\n");
}

T_Position getPositionInitiale() {
	return positionInitiale ;
}

void afficherPosition(T_Position p) {
	int i; int delta; 
	for(i=0;i<NBCASES;i++) {
		printf("%3d : %3d : %s", i, p.cols[i].nb, COLNAME(p.cols[i].couleur));
		delta = 0; 
		if (p.evolution.bonusR == i)  delta++; 
		if (p.evolution.bonusJ == i)  delta++;
		if (p.evolution.malusR == i)  delta--;
		if (p.evolution.malusJ == i)  delta--;
		if (delta>0) printf(" [Evolution:+%d]\n",delta);
		else if (delta<0) printf(" [Evolution:%d]\n",delta); 
		else printf("\n");
	}
	
}


T_ListeCoups getCoupsLegaux(T_Position p) {
	T_ListeCoups l ={0};

	// Pour chaque case, 
	// Si cette contient une colonne non vide, 
	// Pour chaque voisin de cette colonne, 
	// Si la somme colO+colA<= 5, 
	// ajouter ce coup 

	int cO, cD, iV; // case Origine, case Destination, indice Voisin
	T_Voisins v; 
	
	for(cO=0;cO<NBCASES;cO++) {
		printf1("case %d\n",cO); 
		if (p.cols[cO].nb == VIDE ) {printf0("vide!\n"); continue;}
		v = getVoisins(cO); 
		for(iV=0;iV<v.nb;iV++) {
			cD = v.cases[iV]; 
			printf2("voisin %d : case %d\n",iV, cD);
			if (p.cols[cD].nb == VIDE ) {printf0("vide!\n"); continue;} // ajout par tomnab 21/03/2018
			if (p.cols[cO].nb + p.cols[cD].nb <= 5) {
				printf0("possible !\n");
				addCoup(&l, cO,cD); 
			}
		}
	}

	return l; 
}


void addCoup(T_ListeCoups * pL, octet origine, octet destination) {
	pL->coups[pL->nb].origine = origine; 
	pL->coups[pL->nb].destination = destination; 
	pL->nb++; 
}

void afficherListeCoups(T_ListeCoups l) {
	int i; 
	for(i=0;i<l.nb;i++) {
		printf("%3d : %3d -> %3d\n", i, l.coups[i].origine, l.coups[i].destination); 
	}
}

octet estValide(T_Position p, octet origine, octet destination) {

	T_Voisins v; int i;
	

	// vérifie la légalité d'un coup 
	if (p.cols[origine].nb == VIDE) { 
		printf("jouerCoup impossible : la colonne %d est vide ! \n", origine);
		return FAUX;  
	} 

	if (p.cols[destination].nb == VIDE) { 
		printf("jouerCoup impossible : la colonne %d est vide ! \n", destination);
		return FAUX;  
	} 

	if (p.cols[origine].nb + p.cols[destination].nb > 5) {
		printf("jouerCoup impossible : trop de jetons entre %d et %d ! \n", origine, destination);
		return FAUX;  		
	}

	// Il faut aussi vérifier accessibilité !!
	v= getVoisins(origine);
	for (i=0;i<v.nb;i++)
		if (v.cases[i]==destination) return VRAI;
	
	printf("jouerCoup impossible : cases %d et %d inaccessibles! \n", origine, destination);	
	return FAUX;
}


T_Position jouerCoup(T_Position p, octet origine, octet destination) {
	// NB : p est une copie de la position !!

	if (!estValide(p,origine,destination)) return p;

	// Joue un coup 
	p.cols[destination].nb += p.cols[origine].nb; 
	p.cols[destination].couleur = p.cols[origine].couleur; 
	p.cols[origine].nb = VIDE; 
	p.cols[origine].couleur = VIDE; 
	
	// Il faut mettre à jour les pions évolution
	if (p.evolution.bonusR == origine) p.evolution.bonusR=destination;
	if (p.evolution.bonusJ == origine) p.evolution.bonusJ=destination;
	if (p.evolution.malusR == origine) p.evolution.malusR=destination;
	if (p.evolution.malusJ == origine) p.evolution.malusJ=destination;
	
	// On inverse le trait
	p.trait = (p.trait == JAU) ? ROU : JAU;

	// renvoie la nouvelle position 
	return p; 
}


	

T_Score evaluerScore(T_Position p) {
	T_Score s ={0};
	int i;
 
	for(i=0;i<NBCASES;i++) {
		if (p.cols[i].nb != VIDE)  {
			if (p.cols[i].couleur == JAU) {
				s.nbJ++; 
				if (p.cols[i].nb == 5)  s.nbJ5++; 
			} else {
				s.nbR++; 
				if (p.cols[i].nb == 5)  s.nbR5++; 
			}
		}
	}
	
	// partie évolution 	
	if ( (p.cols[p.evolution.bonusR].nb != VIDE) && (p.cols[p.evolution.bonusR].couleur == JAU)) {s.nbJ++;}
	if ( (p.cols[p.evolution.bonusR].nb != VIDE) && (p.cols[p.evolution.bonusR].couleur == ROU)) {s.nbR++;} 
	if ( (p.cols[p.evolution.bonusJ].nb != VIDE) && (p.cols[p.evolution.bonusJ].couleur == JAU)) {s.nbJ++;}
	if ( (p.cols[p.evolution.bonusJ].nb != VIDE) && (p.cols[p.evolution.bonusJ].couleur == ROU)) {s.nbR++;}
	if ( (p.cols[p.evolution.malusR].nb != VIDE) && (p.cols[p.evolution.malusR].couleur == JAU)) {s.nbJ--;}
	if ( (p.cols[p.evolution.malusR].nb != VIDE) && (p.cols[p.evolution.malusR].couleur == ROU)) {s.nbR--;}
	if ( (p.cols[p.evolution.malusJ].nb != VIDE) && (p.cols[p.evolution.malusJ].couleur == JAU)) {s.nbJ--;}
	if ( (p.cols[p.evolution.malusJ].nb != VIDE) && (p.cols[p.evolution.malusJ].couleur == ROU)) {s.nbR--;}


	return s; 
}

void afficherScore(T_Score s) {
	printf("J: %d (%d piles de 5) - R : %d (%d piles de 5)\n", s.nbJ, s.nbJ5, s.nbR, s.nbR5);
}

