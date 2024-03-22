#include "biblioLC.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


Livre* creer_livre(int num,char* titre,char* auteur){
	Livre *l = (Livre*)(malloc(sizeof(Livre)));
	if (l == NULL) { 	//Si la mémoire n'est pas bien allouée
		printf("Erreur: Impossible d'allouer de la mémoire pour le livre.\n");
		return NULL;
	}		
	l->num = num;
	l->titre = strdup(titre);    //il faut allouer de la mémoire pour le lh->titre et lh->auteur
	l->auteur = strdup(auteur);
	l->suiv = NULL;
	return l;
}


void afficher_livre(Livre* l) {
	if (l != NULL) {
		printf("num: %d, titre: %s, auteur: %s \n",l->num,l->titre,l->auteur);
	}
}


void liberer_livre(Livre* l){
	if (l != NULL) {
		free(l->titre);
		free(l->auteur);
		free(l);
	}
}


Biblio* creer_biblio(){
	Biblio *b = (Biblio*)(malloc(sizeof(Biblio)));
	if (b == NULL) { 	//Si la biblio n'est pas bien allouée
		printf("Erreur: Impossible d'allouer de la mémoire pour la biblio.\n");
		return NULL;
	}	
	b->L = NULL;
	return b;
}


void liberer_biblio(Biblio* b){
	if (b == NULL) {
		return ;
	}
	Livre *tete = b->L;
	Livre *tmp;
	while (tete) {  //chaque fois libérer la tête de la liste chaînée
		tmp = tete->suiv;
		liberer_livre(tete);
		tete = tmp;
	}
	free(b);
}


void afficher_biblio(Biblio* b) {
	if (b == NULL) {
		return ;
	}
	Livre *tmp = b->L;
	while (tmp) {
		afficher_livre(tmp);
		tmp = tmp->suiv;
	}
}


Livre* rechercher_par_numero(Biblio* b, int num) {
	if (b == NULL) {
		return NULL;
	}
	Livre *tmp = b->L;
	while (tmp) {    //parcourir la liste et verifier si le num est égalité
		if (tmp->num == num) {
			return tmp;
		}
		tmp = tmp->suiv;
	}
	return NULL;
}


Livre* rechercher_par_titre(Biblio* b, char* titre) {
	if (b == NULL) {
		return NULL;
	}
	Livre *tmp = b->L;
	while (tmp) {   //parcourir la liste
		if (strcmp(tmp->titre,titre) == 0) {  //si les titres sont le même
			return tmp;
		}
		tmp = tmp->suiv;
	}
	return NULL;
}


void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur){
	Livre *l = creer_livre(num,titre,auteur);
	if (l) { 	//Si la mémoire est bien allouée
		if (b == NULL) {
			b = creer_biblio();
			if (b == NULL) {  //si la mémoire n'est pas bien allouée
                printf("Erreur: impossible de créer une nouvelle bibliothèque.\n");
                liberer_livre(l); 
                return ;
            }
		}
		l->suiv = b->L;
		b->L = l;
	} else {
		printf("la mémoire non allouée.\n");
		return;
	}
}


Biblio* rechercher_livres_meme_auteur(Biblio* b, char* auteur) {
	if (b == NULL) {
		return NULL;
	}
	Livre *tmp = b->L;
	Biblio *newBiblio = creer_biblio();
	while (tmp) {
		if (strcmp(tmp->auteur,auteur) == 0) { 	//si d'un même auteur
			inserer_en_tete(newBiblio,tmp->num,tmp->titre,tmp->auteur);
		}
		tmp = tmp->suiv;
	}
	return newBiblio;
}


void supprimer_livre(Biblio* b, int num, char* titre, char* auteur) {
	if (b == NULL) {
		return ;
	}
	Livre *tmp = b->L; 
	Livre *precedent = NULL;
	while (tmp) {
		if ((tmp->num == num) && (strcmp(tmp->titre,titre) == 0) && (strcmp(tmp->auteur,auteur) == 0)) {
			if (precedent == NULL) { // si supprimer la tête
				b->L = tmp->suiv;
			} else {
				precedent->suiv = tmp->suiv;
			}
			liberer_livre(tmp);
			return ;
		} else {
			precedent = tmp;
			tmp = tmp->suiv;
		}
	}
}


Biblio* fusionner_biblio(Biblio* b1, Biblio* b2) {
	if (b2 == NULL) {
		return b1;
	}
	if (b1 == NULL) {   //faire bh1 être vers bh2 et free(bh2) seulement
		b1 = b2;
		free(b2);
		return b1;
	}
	Livre *tmp = b1->L;
	while (tmp->suiv) {
		tmp = tmp->suiv;
	}
	tmp->suiv = b2->L;	
	free(b2);
	return b1;
}


Biblio* rechercher_livres_identiques(Biblio* b) {
	if (b == NULL) {
		return NULL;
	}
	Livre *tmp1 = b->L;
	Livre *tmp2;
	Biblio *b_iden = creer_biblio();     //bibliothèque des livres identiques
	while (tmp1) {     //parcourir la liste chaînée
		tmp2 = tmp1->suiv;
		while (tmp2) {   //parcourir les éléments restes
			if ((strcmp(tmp2->titre,tmp1->titre) == 0) && (strcmp(tmp2->auteur,tmp1->auteur) == 0)) {
				inserer_en_tete(b_iden,tmp2->num,tmp2->titre,tmp2->auteur); 
				break;
			}
			tmp2 = tmp2->suiv;
		}
		tmp1 = tmp1->suiv;
	} 
	return b_iden;
}














