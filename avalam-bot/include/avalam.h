#define FAUX 0
#define VRAI 1


// Vainqueurs des parties et joueurs au trait 
#define EGALITE 0
#define VIDE 0
#define JAU 1
#define ROU 2

#define NBCASES 48
#define UNKNOWN 255

#define COLNAME(c) ((c==ROU) ? "rouge" : "jaune")

// Pour les exports JSON ////////////////////////////////////////////
#define STR_NB "\"nb\""
#define STR_COULEUR "\"couleur\""
#define STR_TURN "\"trait\""
#define STR_COLS "\"cols\""

#define STR_FEN "\"fen\""
#define STR_BONUS_J "\"bonusJ\""
#define STR_BONUS_R "\"bonusR\""
#define STR_MALUS_J "\"malusJ\""
#define STR_MALUS_R "\"malusR\""
#define STR_SCORE_J "\"scoreJ\""
#define STR_SCORE_J5 "\"scoreJ5\""
#define STR_SCORE_R "\"scoreR\""
#define STR_SCORE_R5 "\"scoreR5\""

#define STR_NUMDIAG "\"numDiag\""
#define STR_NOTES "\"notes\""

#define STR_COUPS "\"coups\""
#define STR_ORIGINE "\"o\""
#define STR_DESTINATION "\"d\""
#define STR_J "\"j\""
#define STR_R "\"r\""
#define STR_JOUEURS "\"joueurs\""

#define STR_NOM "\"nom\""
#define STR_SCORE "\"score\""
#define STR_RONDES "\"rondes\""
#define STR_RONDE "\"ronde\""
#define STR_PARTIES "\"parties\""
#define STR_RESULTAT "\"resultat\""
#define STR_STATUT "\"statut\""

#ifdef __DEBUG__
	#define printf0(p) printf(p)
	#define printf1(p,q) printf(p,q)
	#define printf2(p,q,r) printf(p,q,r)
	#define printf3(p,q,r,s) printf(p,q,r,s)
	#define printf4(p,q,r,s,t) printf(p,q,r,s,t)
	#define whoamid(p) whoami(p)
	#define whopd(p) whop(p)
	#define whojd(p) whoj(p)
	#define whoamjd() whoamj()
#else
	#define printf0(p)
	#define printf1(p,q)
	#define printf2(p,q,r)
	#define printf3(p,q,r,s)
	#define printf4(p,q,r,s,t)
	#define whoamid(p)
	#define whoamjd()
	#define whopd(p)
	#define whojd(p)
#endif

//verif appels systèmes 

#define CHECK_IF(sts,val,msg) \
if ((sts) == (val)) {fprintf(stderr,"erreur appel systeme\n");perror(msg); exit(-1);}

#define CHECK_DIF(sts,val,msg) \
if ((sts) != (val)) {fprintf(stderr,"erreur appel systeme\n");perror(msg); exit(-1);}

typedef unsigned char octet; 

typedef struct {
	octet nbJ; 	octet nbJ5; // total et piles de 5 pour les jaunes 
	octet nbR;	octet nbR5; // total et piles de 5 pour les rouges 
} T_Score;

typedef struct {
	octet nb; 
	octet cases[8]; // il peut y en avoir moins... ils vaudront 0
} T_Voisins; 

typedef struct {
	octet nb; 	// nb d'elts dans la colonne 
	octet couleur;  // couleur du sommet 
} T_Colonne; 

typedef struct { 
	octet bonusJ;
	octet malusJ; 
	octet bonusR;
	octet malusR; 
} T_Evolution;

typedef struct { 
	octet trait; 
	// octet numCoup; // A ajouter
	T_Colonne cols[NBCASES];
	T_Evolution evolution;
} T_Position;

typedef struct {
	octet origine; 
	octet destination;
} T_Coup;

typedef struct {
	int nb; 
	T_Coup coups[8*NBCASES]; 
} T_ListeCoups; 

octet nbVoisins(octet numCase); 
T_Voisins getVoisins(octet numCase); 
void listerVoisins(octet numCase); 
T_Position getPositionInitiale();
void afficherPosition(T_Position p); 
void addCoup(T_ListeCoups * pL, octet origine, octet destination);
void afficherListeCoups(T_ListeCoups l);
T_Position jouerCoup(T_Position p, octet origine, octet destination) ;
T_ListeCoups getCoupsLegaux(T_Position p) ; 
T_Score evaluerScore(T_Position p);
void afficherScore(T_Score s); 

