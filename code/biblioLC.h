#ifndef BIBILOC_H
#define BIBILOC_H

typedef struct livre{ 
	int num;                //numéro du livre
	char *titre;		    //titre du livre (pointeur de chaînée de caractère)
	char *auteur;			//auteur du livre (pointeur de chaînée de caractère)
	struct livre * suiv;	//pointeur vers le livre suivant
} Livre;


typedef struct{ 	//Tete fictive
	Livre* L;  		//Premier element
} Biblio;


/* créer un livre */
Livre* creer_livre(int num,char* titre,char* auteur);

/* réaliser une désallocation */
void liberer_livre(Livre* l); 

/* afficher une Livre */
void afficher_livre(Livre* l);

/* créer une bibliothéque vide */
Biblio* creer_biblio(); 

/* libèer la mémoire occupée par une bibliothèque */
void liberer_biblio(Biblio* b); 

/* l’affichage d’une bibliothèque */
void afficher_biblio(Biblio* b); 

/* la recherche d’un ouvrage par son numéro */
Livre* rechercher_par_numero(Biblio* b, int num); 

/* la recherche d’un ouvrage par son titre */
Livre* rechercher_par_titre(Biblio* b, char* titre); 

/* ajoute un nouveau livre à la bibliothèque */
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur); 

/* la recherche de tous les livres d’un même auteur */
Biblio* rechercher_livres_meme_auteur(Biblio* b, char* auteur); 

/* la suppression d’un ouvrage */
void supprimer_livre(Biblio* b, int num, char* titre, char* auteur); 

/* la fusion de deux bibliothèques */
Biblio* fusionner_biblio(Biblio* b1, Biblio* b2);

 /* la recherche de tous les ouvrages identiques */
Biblio* rechercher_livres_identiques(Biblio* b); 

#endif


