#include "biblioH.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAILLE 5000

int fonctionClef(char* auteur) {
	int cle = 0;
	char *tmp = auteur;         
	while(*tmp != '\0') {        //Parcourir chaque caractère de la chaîne auteur
		cle = cle + (int)(*tmp);   //Stocker le code ASCII des lettres dans cle
		tmp++;
	}
	return cle;
}


LivreH* creer_livreH(int num,char* titre,char* auteur) {
	LivreH *lh = (LivreH*)(malloc(sizeof(LivreH)));
	if (lh == NULL) { 	//Si la mémoire n'est pas bien allouée
		printf("Erreur: Impossible d'allouer de la mémoire pour le livreH.\n");
		return NULL;
	}	
	lh->clef = fonctionClef(auteur);
	lh->num = num;
	lh->titre = strdup(titre);     //il faut allouer de la mémoire pour le lh->titre et lh->auteur
	lh->auteur = strdup(auteur);
	lh->suivant = NULL;
	return lh;
}


void liberer_livreH(LivreH* l) {
	if (l != NULL) {    //vérifier que l n'est pas NULL
		free(l->titre);
		free(l->auteur);
		free(l);
	}
}


BiblioH* creer_biblioH(int m) {
	BiblioH *bh = (BiblioH*)(malloc(sizeof(BiblioH)));
	if (bh == NULL) { 	//Si la mémoire n'est pas bien allouée
		printf("Erreur: Impossible d'allouer de la mémoire pour le BiblioH.\n");
		return NULL;
	}	
	bh->nE = 0;
	bh->m = m;
	bh->T = (LivreH**)(malloc(sizeof(LivreH*) * m));  //le table de hachage de taille m
	for (int i=0;i<m;i++) {
		bh->T[i] = NULL;
	}
	return bh;
}


void liberer_biblioH(BiblioH* b) {
	if (b != NULL) {
		LivreH **T = b->T;
		for (int i=0;i<b->m;i++) {
			if (T[i] != NULL) {   //si il y a des livre à l'index du table de hachage
				LivreH *tmp = T[i];
				while (tmp != NULL) {  //parcourir le liste chaînée et libérer chaque élément
					LivreH *suivant = tmp->suivant;
					liberer_livreH(tmp);
					tmp = suivant;
				}
			}
		}
		free(T);   
		free(b);
	}
}


int fonctionHachage(int cle, int m) {
	double A = (sqrt(5.0) - 1) / 2;
	return (int)(m * (cle*A - (int)(cle*A)));
}


void inserer(BiblioH* bh,int num,char* titre,char* auteur) {
	LivreH *lh = creer_livreH(num,titre,auteur);
	if (bh == NULL) {
		bh = creer_biblioH(TAILLE);
	}
	int index = fonctionHachage(fonctionClef(auteur),bh->m);  //trouver l'index dans le table de hachage directement
	lh->suivant = bh->T[index];   //ajouter à la tête de la liste chaînée
	bh->T[index] = lh;
	bh->nE++;
}


void afficher_livreH(LivreH* lh) {
	if (lh != NULL) {
		printf("clef: %d,num: %d, titre: %s, auteur: %s \n",lh->clef,lh->num,lh->titre,lh->auteur);
	}
}


void afficher_biblioH(BiblioH* bh) {
	if (bh == NULL) {
		return ;
	}
	printf("nombre d’elements contenus : %d \n",bh->nE);
	int cpt = 0;    //compteur d'éléments
	for (int i=0;i<bh->m;i++) {
		if (cpt >= bh->nE) {    //si on a déjà parcourit tous les éléments
			break;
		}
		if (bh->T[i] != NULL) {
			LivreH *tmp = bh->T[i];  
			while(tmp != NULL) {
				afficher_livreH(tmp);
				tmp = tmp->suivant;
				cpt++;
			}
		}
	}
	return ;
}


LivreH* rechercher_par_numero_H(BiblioH* bh, int num) {
	if (bh == NULL) {
		return NULL;
	}
	int cpt = 0;
	for (int i=0;i<bh->m;i++) {
		if (cpt >= bh->nE) {    //si on a déjà parcourit tous les éléments
			break;
		}
		if (bh->T[i] != NULL) {
			LivreH *tmp = bh->T[i];
			while(tmp != NULL) {
				if (tmp->num == num) {  //Vérifie si les auteurs ont la même clé
					return tmp;
				}
				tmp = tmp->suivant;
				cpt++;
			}
		}
	}
	return NULL;
}


LivreH* rechercher_par_titre_H(BiblioH* bh, char* titre) {
	if (bh == NULL) {
		return NULL;
	}
	int cpt = 0;
	for (int i=0;i<bh->m;i++) {
		if (cpt >= bh->nE) {
			break;
		}
		if (bh->T[i] != NULL) {
			LivreH *tmp = bh->T[i];
			while(tmp != NULL) {
				if (strcmp(tmp->titre,titre)==0) {  //'tmp->titre == titre'
					return tmp;
				}
				tmp = tmp->suivant;
				cpt++;
			}
		}
	}
	return NULL;
}


BiblioH* rechercher_livres_meme_auteur_H(BiblioH* bh, char* auteur) {
	if ((bh==NULL) || (bh->T==NULL)) {
		return NULL;
	}
	int index = fonctionHachage(fonctionClef(auteur),bh->m); //l'index dans la table hachage
	BiblioH *bh_new = creer_biblioH(bh->m);
	LivreH *tmp = bh->T[index];
	while (tmp != NULL) {
		if (tmp->clef == fonctionClef(auteur)) { 	//si l'autuer est la même
			inserer(bh_new,tmp->num,tmp->titre,tmp->auteur);
		}
		tmp = tmp ->suivant;
	}
	
	return bh_new;
}


void supprimer_livreH(BiblioH* bh, int num, char* titre, char* auteur) {
	if ((bh==NULL) || (bh->T==NULL)) {  //si biblioH ou la table hachage est NULL
		return ;
	}
	int index = fonctionHachage(fonctionClef(auteur),bh->m); //l'index dans la table hachage
	LivreH *tmp = bh->T[index];
	LivreH *precedent = NULL;
	while (tmp != NULL) {
		if((tmp->num==num) && (strcmp(tmp->titre,titre)==0) && (tmp->clef == fonctionClef(auteur))) {
			if (precedent == NULL) {    //si supprimer la tête
				bh->T[index] = tmp->suivant;
			} else {	//sinon
				precedent->suivant = tmp->suivant;
			}
			liberer_livreH(tmp);
			return ;
		}
		precedent = tmp;
		tmp = tmp->suivant;
	}
}


BiblioH* fusionner_biblioH(BiblioH* bh1, BiblioH* bh2) {
	if ((bh2 == NULL) || (bh2->nE == 0)) {  //si rien n'a besoin de fusionner
		return bh1;
	}
	if (bh1 == NULL) {   //si bh1 est NULL, on peut faire bh1 être vers bh2 et free(bh2) seulement
		bh1 = bh2;
		free(bh2);   
	}
	for (int i=0;i<bh2->m;i++) {
		LivreH *tmp = bh2->T[i];   //pour chaque element dans bh2, on l'inserer à bh1
		while (tmp != NULL) {
			inserer(bh1,tmp->num,tmp->titre,tmp->auteur);
			tmp = tmp->suivant;
		}
	}
	liberer_biblioH(bh2);
	return bh1;
}


BiblioH* rechercher_livres_identiques_H(BiblioH* bh) {
	if ((bh == NULL) || (bh->nE <= 1)) {  //si bh == NULL ou il n'y pas au moins 2 elements dans bh2
		return NULL;
	}
	BiblioH *bh_new = creer_biblioH(bh->m);   //bibliothèque des livres identiques
	for (int i=0;i<bh->m;i++) {
		LivreH *tmp = bh->T[i];
		while (tmp != NULL) {  //si il y a des éléments à l'index
			LivreH *suiv = tmp->suivant;
			while (suiv != NULL) {  //parcourir les éléments restes
				// Vérifie si les titres des livres sont identiques et si les livres ont la même clé
				if ((strcmp(tmp->titre,suiv->titre)==0) && (tmp->clef == fonctionClef(suiv->auteur))) {  //dans la même liste chaînée, la même clef ==> le même auteur
					inserer(bh_new,suiv->num,suiv->titre,suiv->auteur); // Insère le livre identique dans la nouvelle bibliothèque
					break;
				}
				suiv = suiv->suivant;
			}
			tmp = tmp->suivant;
		}
	}
	return bh_new;
}















