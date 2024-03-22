#ifndef BIBLIOH_H
#define BIBLIOH_H

typedef struct livreh{
	int clef;  		// la clé utilisée pour l'indexation dans la table de hachage
	int num;   		// le numéro du livre
	char *titre;  	// le titre du livre (chaîne de caractères)
	char *auteur; 	// l'auteur du livre (chaîne de caractères)
	struct livreh *suivant; 
} LivreH;

typedef struct table {
	int nE; 	/*nombre d’elements contenus dans la table de hachage */
	int m; 		/*taille de la table de hachage */
	LivreH** T; /*table de hachage avec resolution des collisions par chainage */
} BiblioH;


/* obtenir la clé associée à la livre */
int fonctionClef(char* auteur);

/* créer un livreh */
LivreH* creer_livreH(int num,char* titre,char* auteur);

/* librer le mémoire d'un livreh */
void liberer_livreH(LivreH* l);

/* créer une biblioH (table de hachage)*/
BiblioH* creer_biblioH(int m);

/* liberer le mémoire d'une biblioH (table de hachage)*/
void liberer_biblioH(BiblioH* bh);

/* la définition de la fonction de hachage, renvoie l'index dans la table de hachage */
int fonctionHachage(int cle, int m);

/* ajoute un nouveau livre à la bibliothèque hachage */
void inserer(BiblioH* bh,int num,char* titre,char* auteur);

/* afficher une Livre */
void afficher_livreH(LivreH* lh);

/* afficher une biblio hachage */
void afficher_biblioH(BiblioH* bh);

/* la recherche d’un ouvrage par son numéro */
LivreH* rechercher_par_numero_H(BiblioH* bh, int num); 

/* la recherche d’un ouvrage par son titre */
LivreH* rechercher_par_titre_H(BiblioH* bh, char* titre);

/* la recherche de tous les livres d’un même auteur */
BiblioH* rechercher_livres_meme_auteur_H(BiblioH* bh, char* auteur);

/* la suppression d’un ouvrage */
void supprimer_livreH(BiblioH* bh, int num, char* titre, char* auteur);

/* la fusion de deux bibliothèques */
BiblioH* fusionner_biblioH(BiblioH* bh1, BiblioH* bh2);

/* la recherche de tous les ouvrages identiques */
BiblioH* rechercher_livres_identiques_H(BiblioH* bh);


#endif



